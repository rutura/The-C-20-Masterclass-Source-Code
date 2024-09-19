/*
    . Exploring std::string_view
    . Topics: 
        . The problem
        . The solution
        . Construction
        . Visualizing the original string
        . Changing the view window
        . Lifetime
        . Data
        . Non-null terminated strings
        . Behaviors

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
    //string_view_the_problem();
    //string_view_the_solution();
    //string_view_construction();
    //std_string_view_visualizes_original_string();
    //std_string_view_change_view_window();
    //std_string_view_lifetime();
    //std_string_view_data();
    //std_string_view_non_null_terminated_strings();
    std_string_view_behaviors();
}