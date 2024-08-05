/*
    . Move semantics: 
        .#1: Lvalues and rvalues
            . see move_semantics_01.ixx

        .#2: Rvalue references
            . see move_semantics_02.ixx

        .#3: Moving temporaries around
            . see move_semantics_03.ixx

        .#4: Move constructor and move assignment operator
            . see move_semantics_04.ixx

        .#5: Moving lvalues with std::move
            . see move_semantics_05.ixx


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
  //move_semantics_01_demo();
  //move_semantics_02_demo();
  //move_semantics_03_demo();
  //move_semantics_04_demo();
  move_semantics_05_demo();

}