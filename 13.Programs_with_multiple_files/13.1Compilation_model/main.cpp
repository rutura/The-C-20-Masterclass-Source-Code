/*
    . Compilation model: 
        . Explains how C++ programs are compiled and shows a practical example with GCC
        
        . ATTENTION: Removed fmt here to reduce compilation complexity.
        .#1: compiling modules
            . g++ -fmodules-ts -x c++-system-header iostream
            . g++ -fmodules-ts -c -x c++ point.ixx
            . g++ -fmodules-ts -c -x c++ utilities.ixx
            . g++ -fmodules-ts -c point_impl.cpp
            . g++ -fmodules-ts main.cpp point.o point_impl.o utilities.o -o rooster.exe


        .#2: Compiling header based programs: Reproduce what's in version #1 of the course.
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
    use_point();
}