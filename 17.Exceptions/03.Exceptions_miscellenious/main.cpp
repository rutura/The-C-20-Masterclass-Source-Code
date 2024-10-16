/*
    . Exceptions - Miscellaneous subjects: 
        .#1: Rethrowing exceptions

        .#2: Custom termination
            . see the main.cpp file.

        .#3: Ellipsis catch all block
            . see ellipsis_catch_all.ixx

        .#4: Noexcept specifier
            . see noexcept_specifier.ixx

        .#5: Exceptions in destructors
            . see exceptions_in_destructors.ixx

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
#include <chrono>
#include <exception>
#include <fmt/format.h>
#include <thread>


import utilities;

void our_terminate_function()
{
  fmt::println("Our custom terminate function called");
  fmt::println("Program will terminate in 10s ...");
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));// Wait 10 more seconds
  std::abort();
}

int main() {
    //rethrowing_exceptions_demo();

    //Custom termination
    /*
    // std::set_terminate(&our_terminate_function);
    std::set_terminate([]() {
        fmt::println("Our custom terminate function called");
        fmt::println("Program will terminate in 10s ...");
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));// Wait 10 more seconds
        std::abort();
    });

    throw 1;
    */

    //exceptions_1_demo();
    //exceptions_3_demo();
    //exceptions_4_demo();
    //exceptions_5_demo();
}