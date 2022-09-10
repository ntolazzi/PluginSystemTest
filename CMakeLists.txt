cmake_minimum_required(VERSION 3.23)
project(PluginTest)

set(CMAKE_CXX_STANDARD 20)

add_library(Plugin1 SHARED plugin1.cpp)
add_library(Plugin2 SHARED plugin2.cpp)
add_executable(PluginTest main.cpp)
