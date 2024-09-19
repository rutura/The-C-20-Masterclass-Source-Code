/*
    . Standard expceptions: 
        .#1: Catching standard exceptions
            . See catching_std_exceptions.ixx 

        .#2: Throwing standard exceptions
            . See throwing_std_exceptions.ixx

        .#3: Deriving from standard exceptions
            . See deriving_from_std_exceptions.ixx
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
    //catching_std_exceptions_demo();
    //throwing_std_exceptions_demo();
    deriving_from_std_exceptions_demo();
}