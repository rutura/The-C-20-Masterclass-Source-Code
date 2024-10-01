/*
    . Exceptions and objects: 
        .#1: Throwing class objects
            . see throw_class_objects.ixx

        .#2: Throwing class objects with inheritance
            . see throw_class_objects_with_inheritance.ixx

        .#3: Polymprphic exceptions
            . see polymorphic_exceptions.ixx


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
    //throw_class_objects_demo();
    //throw_class_objects_with_inheritance_demo();
    polymorphic_exceptions_demo();
}