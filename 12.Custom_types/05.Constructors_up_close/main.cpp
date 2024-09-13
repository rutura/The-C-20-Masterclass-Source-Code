/*
    . Constructors up close
        . #1: default parameters for constructors
        . #2: Initializer lists for constructors
        . #3: Explicit constructors
        . #4: Constructor delegation
        . #5: Copy constructors
        . #6: Objects stored in arrays are copies
        . #7: Move constructors 
        . #8: Deleted constructors
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
    //constructor_default_parameters();
    //constructor_initializer_lists();
    //explicit_constructors();
    //constructor_delegation();
    //copy_constructors();
    //arrays_store_copies();
    //move_constructors();
}