/*
    . Final, access specifiers and the more on the virtual keyword: 

        .#1: Final
            . see inh_poly_1.ixx
        .#2: Final and override are not keywords
            . see inh_poly_2.ixx

        .#3: . Exploring the case where when the same function is public in the base class and private in the derived class
                . When polymorphism is used, the function in the derived class is called.
                . When static binding is used, the function in the base class is called.
                . see inh_poly_3.ixx

        .#4: Virtual functions with default arguments
            . see inh_poly_4.ixx

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

import utilities;

int main() {

    //inh_poly_1_demo();
    //inh_poly_2_demo();
    //inh_poly_3_demo();
    inh_poly_4_demo();
}