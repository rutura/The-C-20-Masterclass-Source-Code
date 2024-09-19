/*
    . Exploring the std::array collection type in C++.
    . Goal: 
        . Show that std::array is one of your best default choices when you need to deal with sequence data in C++.
    . Benefits: 
        . Each collection knows its size.
        . Easy to pass to functions (doesn't need to pass the size as a separate parameter).
        . Convenient functions to get the front and back elements.
        . Can be compared using comparison operators (==, !=, <, <=, >, >=).
        . Can assign a std::array to another std::array.
        . Can store an std::array in another container.
        . You don't have to mess with low lever arrays and pointers. 

    . Points to make: 
        . The differences between at() and operator[].
        . std::array should be your choice if you know the size of the collection at compile time, and you won't need to change its size.
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
    do_work();
}