/*
    . Concepts and class templates: 
        .#1: class templates and concepts
            . see class_template_concepts_01.ixx

        #2: Built in concepts
            . see class_template_concepts_02.ixx 

        .#3: example 1
            . see class_templates_concepts_03.ixx

        .#4: example 2
            . see class_templates_concepts_04.ixx

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
    //class_templates_concepts_01_demo();
    class_templates_concepts_03_demo();
}