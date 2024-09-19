/*
    .  Fortune teller example 
        .Different versions of the fortune teller program. 
            . From storing predictions as C-style strings to storing them as std::string.
            . From using std::rand() to using std::mt19937.
            . And all in betweens. 

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

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
#include "utilities.h"

int main() {
    //This is our best version so far.
    fortune_teller_version_5();
    return 0; 
}