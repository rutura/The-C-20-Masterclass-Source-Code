/*
    . Operator overloading  and type conversions
        .#1: Custom type conversions
            . Conversion from Number to double [Works]
            . Conversion from Number to Point. Doesn't work because modules have problems 
                with a custom module importing another custom module. Check if this is a problem
                with other compilers (msvc,clang).

        .#2: Implicit conversions for overloaded binary operators
            . If the binary operator (+,-,...) is done as a member, implicit conversions
                won't work for the first operand.


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
    //custom_type_conversions();
    implicit_conversions_for_overloaded_binary_operators();
}