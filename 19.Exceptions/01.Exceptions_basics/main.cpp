/*
    . Exception basics: 
        .#1: Exceptions basics

        .#2: The need for exceptions

        .#3: Exceptions at different levels

        .#4: Multiple handlers for an exception

        .#5: Nested try blocks


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
    //try_catch_blocks_demo();
    //need_for_exceptions_demo();
    //exceptions_diff_levels_demo();
    //multiple_handlers_for_exception_demo();
    nested_try_blocks_demo();
}