#include <iostream>
#include <optional>
#include <dlfcn.h>
#include <vector>
#include <filesystem>


typedef void (*load_fct_ptr)();
typedef void* shared_lib_handle;
std::vector<load_fct_ptr> plugin_load_functions;
std::vector<shared_lib_handle> plugin_handles;

std::optional<shared_lib_handle> getFctPtrFromSharedLib(void* lib_handle, const std::string& fct_name){
    auto fct_ptr = dlsym(lib_handle, fct_name.c_str());
    if(!fct_ptr){
        std::cerr << "Could not find function '" << fct_name << "'" << std::endl;
        return {};
    }else{
        return fct_ptr;
    }
}

int main(){
    for(const auto& file: std::filesystem::directory_iterator(".")){
        auto filestring = file.path().string();
        if(filestring.find("Plugin") != std::string::npos) {
            if(filestring.ends_with(".so")){
                std::cout << "Found Plugin: " << filestring << std::endl;
                shared_lib_handle handle = dlopen(filestring.c_str(), RTLD_LAZY);
                if(!handle){
                    std::cerr << "Could not open " << filestring << std::endl;
                    continue;
                }
                plugin_handles.push_back(handle);
                auto fct_ptr = getFctPtrFromSharedLib(handle, "load");
                if(fct_ptr.has_value()){
                    plugin_load_functions.push_back((load_fct_ptr)fct_ptr.value());
                    std::cout << "Added Plugin: " << filestring << std::endl;
                }
            }
        }
    }
    for(const auto& plugin_fct: plugin_load_functions){
        plugin_fct();
    }

    for(auto& handle: plugin_handles){
        dlclose(handle);
    }
    return 0;
}