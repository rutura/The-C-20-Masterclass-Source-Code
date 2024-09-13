/*
    . Inline variables and forward declarations
        . ATTENTION: 
            . This project has no content as of now. It will be filled in after some
                more reference consultation.
            . Its content should sync with the old chapter 32. Program with multiple files.

        .#1: Inline variables and functions

        .#2: Inline variables vs anonymous namespaces

        .#3: Forward declarations
         
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
import utilities;

int main() {
  print_msg("Hello world!");
}