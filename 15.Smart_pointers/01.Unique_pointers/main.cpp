/*
    . Smart pointers
        .#1: Unique pointers

        .#2: Unique pointers as function parameters and return types
            . Uses dog and person classes here.
            . ATTENTION: 
                . In this exhibit, person depends on dog, because a person can adopt a dog.
                . The same problem we've seen where when one custom(user defined) module gcc
                    throws errors shows up here. Try to build this with MSVC or clang and see 
                    how it goes.

        .#3: Unique pointers and arrays.

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
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
#include "utilities.h"

int main() {
    //unique_pointers();
    //unique_pointers_as_func_param_or_return_type();
    unique_pointers_and_arrays();
}