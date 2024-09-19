/*
    . Variable templates and alias templates: 
        .#1: Variable templates
            . see variable_templates.ixx 

        .#2: Alias templates
            . We just use using declarations
            . typedefs are old C++ and we ignore them.
            
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
    //variable_templates_demo();
    template_aliases_demo();
}