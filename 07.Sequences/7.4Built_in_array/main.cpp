/*
    . Exploring built in arrays
    . Topics: 
        Declaration and Initialization:
            Demonstrates how to declare and initialize built-in arrays with and without specific values.

        Accessing and Modifying Elements:
            Shows how to access and modify elements of an array using the subscript operator [].

        Iterating Over an Array:
            Provides examples of iterating over an array using a traditional for loop and a range-based for loop.

        Multidimensional Arrays:
            Illustrates the declaration, initialization, and iteration of a 2D array.

        Size of Arrays:
            Explains how to calculate the number of elements in an array using the sizeof operator.

        Array of Strings:
            Demonstrates the declaration and iteration of an array of C-strings (const char*).

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
    do_work();
}