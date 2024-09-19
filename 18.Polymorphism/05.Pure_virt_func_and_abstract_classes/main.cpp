/*
    . Pure virtual functions and abstract classes: 
        .#1: Pure virtual functions and abstract classes:

        .#2: Abstract classes as interfaces 


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
  //pure_virt_func_abstract_classes_demo();
  abstract_class_interfaces_demo();
}