/*
    . Function pointers: 
        .#1: Function pointers
             see function_pointers_01.ixx 
        .#2: Callback functions: 
            see function_pointers_02.ixx

        .#3: Function pointer aliases
            . see type aliases in function_pointers_02.ixx 
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

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment

#include "utilities.h"

int main() {
    //function_pointers_01_demo();
    //function_pointers_02_demo();
    function_pointers_03_demo();
}