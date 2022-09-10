#include <iostream>

extern "C" void load() {
    std::cout << "Plugin 1 loaded" << std::endl;
}
