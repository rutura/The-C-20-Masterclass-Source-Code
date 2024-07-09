/*
    . Operator overloading 
        .#1: Overload operator+ as a member
            . Inside the class
            . outside
        .#2: Overload operator+ as a non-member
            . Inside
            . Outside

        .#3: Overloading the subscript operator for Point
            . Can only be a member

        .#4: Subscript operator reading and writing

        .#5: Subscript operator for collection types


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
    //overload_plus_operator_as_member();
    //overload_plus_operator_as_non_member();
    //overload_subscript_operator();
    //overload_subscript_reading_writing();
    overload_subscript_operator_for_collection_types();
}