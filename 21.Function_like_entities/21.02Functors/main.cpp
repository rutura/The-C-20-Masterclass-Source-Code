/*
    . Functors:
        .#1: Functor basics:
            . see functors_01.ixx

        .#2: Standard functors
            . see functors_02.ixx

        .#3: Functors with parameters
            . see functors_03.ixx

        .#4: Functors and lambdas
            . Showing that lambdas are implemented as functors behind the scenes.
            . see functors_04.ixx



    . Build instructions:
        . Bare hands with CMake:
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code):
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from
   the start.

        . Can also use presets on the command line.
    . Dependencies:
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

    . Philosophy:
        . All non module looking code should be hidden away in the utilities
   module.

*/

// One line comment
import utilities;

int main() {
     //functors_01_demo(); 
     //functors_02_demo();
     //functors_03_demo();
     functors_04_demo();
}