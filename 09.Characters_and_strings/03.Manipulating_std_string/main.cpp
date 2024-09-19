/*
    . Manipulating characters: 
    . Topics: 
        . std::string: declaration
        . std::string: concatenation
        . std::string: concatenation
        . std::string: access characters
        . std::string: size and capacity
        . std::string: modify

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
    //std_string_declaration();
    //std_string_concatenation();
    //std_string_access_characters();
    //std_string_size_and_capacity();
    std_string_modify();
}