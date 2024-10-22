/*
    . STL, Containers and iterators
        .#1: Common containers: std::vector and std::array
            . see containers_iterators_01.ixx

        .#2: Iterators
            . see containers_iterators_02.ixx
            . Playing with the basics of iterators. 
            . Manually moving forward and printing both std::vector and std::array with one print function.
            . we can adjust the beginning and end of the collection for printing.
            . reverse iterators

        .#3: Constant iterators, std::begin, and std::end
            . see containers_iterators_03.ixx

        .#4: The iterator traits template
            . see containers_iterators_04.ixx


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
    //containers_iterators_01_demo();
    //containers_iterators_02_demo();
    containers_iterators_03_demo();
    //containers_iterators_04_demo();
}