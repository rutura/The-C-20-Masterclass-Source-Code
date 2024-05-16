/*
    . A C++ starter project using CMake and bringing in fmt right out of the box.
    . Uses the CMake presets file from endless sky and modifies it to work with the cl compiler
    . Uses vcpkg as a dependency manager
    . Sets up vs code to have a status bar
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets: 

*/

// One line comment
#include <fmt/format.h>
#include <iostream>

int main()
{

  fmt::println("Hello World!");
  return 0;
}