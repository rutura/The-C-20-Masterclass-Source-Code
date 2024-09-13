/*
    . Exploring built in arrays
    . Topics: 
        . Declaration and initialization
        . Size of an array
        . Array of characters
        . Array bounds
        . Random number generation old style
        . Random number generation modern C++
        . Multi-dimensional array
        . Multi-dimensional array of characters
        
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
    //declaration_and_initialization();
    //size_of_an_array();
    //array_of_characters();
    //array_bounds();
    //random_num_old_style();
    //random_num_modern_cplusplus();
    use_random_numbers();
    return 0; 
}