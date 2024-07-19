/*
    . Polymorphism, casts and destructors
        .#1: Virtual destructors

        .#2: Dynamic casts

        .#3: Polymorphic functions and destructors

        .#4: typeid operator


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
  //virtual_destructors_demo();
  //dynamic_casts_demo();
  //poly_func_and_destructors_demo();
  typeid_operator_demo();
}