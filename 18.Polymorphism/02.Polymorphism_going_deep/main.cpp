/*
    . Polymorphism - going deep:

        .#1: The override keyword

        .#2: Overriding, overloading and hiding

        .#3: Polymorphism at different levels

        .#4: Polymophism with static members

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
   //override_keyword_demo();
   //overloading_overriding_and_hiding_demo();
   //polymorphism_diff_levels_demo();
   //polymorphism_with_static_members_demo();
}