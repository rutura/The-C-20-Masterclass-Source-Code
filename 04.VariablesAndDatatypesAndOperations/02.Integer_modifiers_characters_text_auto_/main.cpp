/*
    . Topics: 
        . Initialzation: 
            . Braced initialization
            . Function style initialization
            . Assignment initialization
            . Integer modifiers
            . Floating point numbers: 
                . Precision
                . Scientific notation
            . Infinity and nan
            . Characters and text
            . auto

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


#include "utilities.h"

int main() {
    do_work();

    return 0;
}