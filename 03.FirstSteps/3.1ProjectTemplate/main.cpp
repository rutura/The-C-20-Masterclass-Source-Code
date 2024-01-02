/*
    . A C++ starter project using CMake and bringing in fmt right out of the box.
    . Uses the CMake presets file from endless sky and modifies it to work with the cl compiler
    . Uses vcpkg as a dependency manager
    . Sets up vs code to have a status bar

*/

//One line comment
#include <iostream>
#include <fmt/format.h>

int main(){

    fmt::print("Hello World!");
    return 0;
}