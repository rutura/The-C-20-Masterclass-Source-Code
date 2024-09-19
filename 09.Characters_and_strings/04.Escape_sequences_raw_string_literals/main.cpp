/*
    . Escape sequences and raw string literals 
    . Topics: 
        . Escape sequences: 
            . \n: New line character
            . \t: Tab character
            . \": Double quote character
            . \\: Backslash character
        . Raw string literals: 
            . R"(string)"
            . No need to escape characters
            . Useful for regular expressions, file paths, etc.

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
    //escape_sequences();
    raw_string_litterals();

}