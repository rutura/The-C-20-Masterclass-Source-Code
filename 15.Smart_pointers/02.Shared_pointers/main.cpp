/*
    . Shared pointes: 
        .#1: Shared pointer basics

        .#2: Shared pointers from unique pointers

        .#3: Shared pointers with arrays

        .#4: Shared pointers as function parameters or return types.
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
    //shared_pointers();
    //unique_pointer_from_shared_pointer();
    //shared_pointers_with_arrays();
    shared_pointers_as_function_parameters_and_return_types();
    

}