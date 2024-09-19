/*
    . Template basics in C++
        .#1: Basic function template

        .#2: Class template basics

        .#3: Template member functions

        .#4: Template parameter types: 
            . type template parameters
            . non-type template parameters

        .#5: Template template parameters
            . We have seen: 
                . non type template parameters
                . type template parameters
            . In this exhibit, we will see template template parameters.
                These are not used commonly but are useful in some cases.
            . See details in template_template_parameters.ixx
        
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
    //function_template_basics_demo();
    //class_template_basics_demo();
    //template_member_functions_demo();
    //template_parameter_types_demo();
    template_template_parameters_demo();
}