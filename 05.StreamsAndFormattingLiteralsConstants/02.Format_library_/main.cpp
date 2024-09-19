/*
    . Format library
        . 
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
        . gcc (can be official container)
        . cmake
        . ninja
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version
*/

// One line comment

//#include <print>
#include "utilities.h"

#include <iostream>


int main() {

    //C++ 23 adds std::print and std::println, but they only work well on Visual C++.
    //We'll stick to fmt going forward.
    /*
    auto value = std::format("Hello, {}!", "world");
    std::cout << value << "\n";
    
    std::print("Hello, {}!", "world\n");
    std::print("Hello, {}!", "world\n");
    std::println("Unformatted table : ");
    std::println("{} {} {}", "Daniel", "Gray", "25");
    std::println("{} {} {}", "Stanley", "Woods", "33");
    std::println("{} {} {}", "Jordan", "Parker", "45");
    std::println("{} {} {}", "Joe", "Ball", "21");
    std::println("{} {} {}", "Josh", "Carr", "27");
    std::println("{} {} {}", "Izaiah", "Robinson", "29");

    std::println("-----");

    std::println("Formatted table : ");
    std::println("{:<10} {:<10} {:<5}", "Lastname", "Firstname", "Age");
    std::println("{:<10} {:<10} {:<5}", "Daniel", "Gray", "25");
    std::println("{:<10} {:<10} {:<5}", "Stanley", "Woods", "33");
    std::println("{:<10} {:<10} {:<5}", "Jordan", "Parker", "45");
    std::println("{:<10} {:<10} {:<5}", "Joe", "Ball", "21");
    std::println("{:<10} {:<10} {:<5}", "Josh", "Carr", "27");
    std::println("{:<10} {:<10} {:<5}", "Izaiah", "Robinson", "29");
    */
    do_work();
}