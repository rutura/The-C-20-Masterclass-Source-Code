/*
    . Prefix and postfix operators: 
        .#1: unary prefix operator+ as member

        .#2: unary prefix operator+ as non member
            . inline and non inline.

        .#3: unary postfix operator+ (member, non-member)





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
    //unary_prefix_operator_as_member();
    //unary_prefix_plus_operator_as_non_member();
    //postfix_plus_operator();
}