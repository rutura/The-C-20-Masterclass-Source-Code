/*
    . Standard expceptions: 
        .#1: Catching standard exceptions
            . See catching_std_exceptions.ixx 

        .#2: Throwing standard exceptions
            . See throwing_std_exceptions.ixx

        .#3: Deriving from standard exceptions
            . See deriving_from_std_exceptions.ixx
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
    //catching_std_exceptions_demo();
    //throwing_std_exceptions_demo();
    deriving_from_std_exceptions_demo();
}