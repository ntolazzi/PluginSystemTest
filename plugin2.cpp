#include <iostream>

extern "C" void load() {
    std::cout << "Plugin 2 loaded" << std::endl;
}
