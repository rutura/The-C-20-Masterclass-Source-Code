/*
    . Third party coroutine types
        .#1: cppcoro
            . see practical_coro_01.ixx 

        .#2: std::generator C++23
            . see practical_coro_02.ixx 

        .#3: synchronous http client without coroutines

        .#4: async client with coroutines
        
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
    //practical_coro_01_demo();
    //practical_coro_02_demo();
}