/*
    . Attributes: 
        . Attributes in C++ are a powerful way to communicate extra information to the compiler without affecting the behavior of the program directly. Attributes from earlier standards like [[noreturn]], [[deprecated]], and [[nodiscard]] help with code readability, diagnostics, and error prevention. Newer attributes in C++20 ([[likely]], [[no_unique_address]]) and C++23 ([[assume]], [[nodiscard("reason")]]) focus on further improving performance and providing clearer guidance.

        . Attributes make C++ code cleaner, more maintainable, and more optimized, and understanding when to use them helps write better software.

        . Compilers have varying levels of support for these attributes.

        . Attributes we have seen are related to functions, but they can also be applied classes, and other entities in C++.

    . Uses vcpkg as a dependency manager
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Note: 
            . There are other ways to build but we'll focus on these two in the course.
            . You can use the docker containers that come with the course for a fully reproducible build environment.
                . one for gcc 14 [link]
                . one for clang 18 [link]

    . Requirements:
        . A modern C++ compiler: 
            . eg: gcc 14, clang 16 or latest msvc. 
        . cmake 3.30 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
            . how to update vcpkg: https://learn.microsoft.com/en-us/vcpkg/about/faq#how-do-i-update-vcpkg
        . A debugger: 
            . eg: gdb, lldb, or the visual studio debugger
        . Goood to have: 
            . Git

        . Editor: 
            . VS Code: 
                . The C++ extension
                . The CMake Tools extension
                . The CMake extension
                . NOTE: These are required to give you the best experience.

        . Know where a binary is: 
            . Linux: which command
                . eg: which ninja
            . Windows: Get-command
                . eg: Get-command ninja

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/
#include <fmt/format.h>

import utilities;


//Static variables in functions: This allows us to keep track of the number of times a function has been called.
void user_login() {
    static size_t login_count = 0;
    ++login_count;

    fmt::println("Welcome back! This is your login attempt number: {}", login_count);
}

int main() {

    //attributes_demo();

    //Function local static variables
    /*
    user_login();
    user_login();
    user_login();
    */

    //recursion
    recursion_demo();



}