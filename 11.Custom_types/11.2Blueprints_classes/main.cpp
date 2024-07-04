/*
    . Exploring classes.
        . Your first class
        . Using constructors
        . Defaulted constructors
        . Setters and getters
        . Class across multiple files
        . Order of constructor and destructor calls
        . Nested classes
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
import cylinder;

int main() {
    //your_first_class();
    //using_constructors();
    //defaulted_constructors();
    //setters_and_getters();
    //class_x_multiple_files();
    //order_of_constr_destr_calls();
    nested_classes();
}