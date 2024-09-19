/*
    . Namespaces: 
        . The basics
            . #1: Creating namespaces
            . #2: Namespaces across multiple files
                    . cylinder, line and point
                    . ATTENTION: When you have a module that depends on another, say a line module
                                 that depends on a Point module, (because a line is made up of two points)
                                 and import the point module in the line module, GCC gives weird compiler 
                                 errors. I haven't tested if this is the case with other compilers, but I trimmed
                                 down this example to remove these dependencies to just highlight the use of namespaces
                                 across different modules. One can always revert to header importation to make this work
                                 though.

            . #3: Default global namespace
            . #4: Built in namespaces
            . #5: Using declarations
            . #6: Anonymous namespaces
            . #7: Nested namespaces.
            . #8: Namespace aliases
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
    //create_namespace();
    //ns_x_multiple_files();
    //default_global_namespace();
    //built_in_namespaces();
    //using_declarations();
    //anonymous_namespace();
    //nested_namespaces();
    namespace_aliases();
}