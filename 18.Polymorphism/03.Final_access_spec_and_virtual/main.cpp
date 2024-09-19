/*
    . Final, access specifiers and the more on the virtual keyword: 
        .#1: Final

        .#2: Final and override are not keywords

        .#3: Polymorphic functions and access specifiers

        .#4: Non polymorphic functions and access specifiers

        .#5: Virtual functions with default arguments

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
  //final_keyword_demo();
  //final_override_not_keywords_demo();
  //poly_func_and_acc_spec_demo();
  //non_polymorphic_func_and_acc_spec_demo();
  virt_func_default_arg_demo();

}