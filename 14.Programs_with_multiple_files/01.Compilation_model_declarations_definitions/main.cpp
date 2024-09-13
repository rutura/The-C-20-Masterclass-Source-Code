/*
    . General name left to figure out later.
        .#1: Compilation model: 
            . Explains how C++ programs are compiled and shows a practical example with GCC
            
            . ATTENTION: Removed fmt here to reduce compilation complexity.
            . compiling modules
                . g++ -fmodules-ts -x c++-system-header iostream
                . g++ -fmodules-ts -c -x c++ point.ixx
                . g++ -fmodules-ts -c -x c++ utilities.ixx
                . g++ -fmodules-ts -c point_impl.cpp
                . g++ -fmodules-ts main.cpp point.o point_impl.o utilities.o -o rooster.exe


            . Compiling header based programs: Reproduce what's in version #1 of the course.
        
        . #2: Declrarations and definitions: Person class: 
            . Compile this using both cmake (with VS Code) and the terminal. Solve problems that show up.
            . Commands: 
                . g++ -fmodules-ts -x c++-system-header iostream
                . g++ -fmodules-ts -x c++-system-header string
                . g++ -fmodules-ts -c -x c++ point.ixx
                . g++ -fmodules-ts -c -x c++ person.ixx
                . g++ -fmodules-ts -c -x c++ utilities.ixx
                . g++ -fmodules-ts -c point_impl.cpp
                . g++ -fmodules-ts -c person_impl.cpp
                . g++ -fmodules-ts main.cpp point.o point_impl.o person.o person_impl.o utilities.o -o rooster.exe
            . Definitions are resolved at link time. Leave them out and you get linker errors.
                . undefined reference to ...

        . #3: One Definition Rule
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