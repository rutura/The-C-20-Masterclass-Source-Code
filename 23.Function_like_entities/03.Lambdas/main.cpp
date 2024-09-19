/*
    . Lambdas: 
        .#1: Lambdas as callbacks
            . see lambdas_01.ixx

        .#2: Capturing by value under the hood
            . see lambdas_02.ixx

        .#3: Capturing by reference under the hood
            . see lambdas_03.ixx

        .#4: Mixing it up
            . see lambdas_04.ixx

        #5: Capturing the this pointers
            . see lambdas_05.ixx


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
    //lambdas_01_demo();
    //lambdas_02_demo();
    //lambdas_03_demo();
    //lambdas_04_demo();
    lambdas_05_demo();


}