/*
    . Exploring inheritance: 
        .#1: Inheritance basics
            . see the inh_basics.ixx file.

        .#2: Protected members
            . see the protected_members.ixx
            . if the name of the namespace matches the name of the function,
                you get redefinition errors. Keep this in mind in utilities.ixx.

        .#3: Playing with base class access specifiers
            . see the base_acc_spec.ixx file.
            . public, protected and private inheritance

        .#4: Deep into private inheritance
            . see priv_inh.ixx 
            . Try this out on GCC and Clang
        .#5: Resurecting members back in context
            . see resurect.ixx


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

*/

// One line comment
#include "utilities.h"

int main() {

    //inheritance_basics();
    //protected_members_func();
    //base_access_specifiers();
    //zooming_on_private_inheritance();
    resurect_members_back_in_context();

}