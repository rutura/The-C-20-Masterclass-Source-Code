/*
    . Exploring the ranges library: 

        .#1: Range algorithms
            see ranges_library_01.ixx

        .#2: Ranges library iterator pair algorithms
            see ranges_library_02.ixx

        .#3: Projections
             see ranges_library_03.ixx

        .#4: Views and range adaptors
            see ranges_library_04.ixx

        .#5: View composition and pipe operator
            see ranges_library_05.ixx

        .#6: Range factories
            see ranges_library_06_demo() in utilities.ixx



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
    //print_msg("Hello world!");
    //ranges_library_01_demo();
    //ranges_library_02_demo();
    //ranges_library_03_demo();
    //ranges_library_04_demo();
    ranges_library_06_demo();
}