/*
    . Concepts: 
        .#1: Basic concepts
            . see concepts_01.ixx

        .#2: Build your own concepts
            . see concepts_02.ixx

        .#3: Zooming in on the requires clause
            . see concepts_03.ixx 

        .#4: Combining concepts
            . see concepts_04.ixx

        .#5: Concepts and auto
            . see concepts_05.ixx

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
    
}