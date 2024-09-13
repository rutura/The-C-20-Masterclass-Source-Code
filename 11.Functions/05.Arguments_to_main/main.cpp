/*
    . Arguments to main: 
        . Grab and use the arguments: the concepts
        . Show calculator example, getting operands and operator from the command line.
            . Multiplication uses the x character, not the * character.
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
#include <fmt/format.h>
import utilities;

int main(int argc, char* argv[]) {

    /*
    fmt::println("We have {} parameters in our program", argc);

    for (size_t i{ 0 }; i < argc; ++i) {
        fmt::println("parameter [{}]: {}", i, argv[i]);
    }
    */
    //Process the arguments from an external function.
    //process_arguments(argc, argv);

    //Call the calculator function
    calculator(argc, argv);
}