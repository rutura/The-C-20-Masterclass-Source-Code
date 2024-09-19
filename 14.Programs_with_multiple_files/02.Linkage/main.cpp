/*
    . ATTENTION: 
        . This project is EMPTY. It will be populated after consulting the references
        . Its content should emulate what we had in the old chapter 32.
    . Linkage: 
        .#1: Linkage basics: The old video content

        .#2: Global external variables

        .#3: Flipping linkage

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
  print_msg("Hello world!");
}