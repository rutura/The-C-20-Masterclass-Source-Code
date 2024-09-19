/*
    . Couroutine basics: 
        .#1: co_await: 
            . see coro_basics_01.ixx

        .#2: co_yield: 
            . see coro_basics_02.ixx 

        .#3: co_return: 
            . see coro_basics_03.ixx

        .#4: custom generator
            . see coro_basics_04.ixx 
            
        .#5: third party coroutines
            . see coro_basics_05.ixx 
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
    //coro_basics_01_demo();
    //coro_basics_02_demo();
    //coro_basics_03_demo();
    coro_basics_04_demo();
}