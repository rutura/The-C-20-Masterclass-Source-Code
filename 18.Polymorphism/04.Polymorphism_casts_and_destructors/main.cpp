/*
    . Polymorphism, casts and destructors
        .#1: Virtual destructors

        .#2: Dynamic casts

        .#3: Polymorphic functions and destructors

        .#4: typeid operator


    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Can also use presets on the command line.
    . Dependencies: 
        . gcc
        . cmake
        . ninja
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

*/

// One line comment
#include "utilities.h"

int main() {
  //virtual_destructors_demo();
  //dynamic_casts_demo();
  //poly_func_and_destructors_demo();
  typeid_operator_demo();
}