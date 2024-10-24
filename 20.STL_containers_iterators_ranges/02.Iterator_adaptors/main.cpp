/*
    . Exploring iterator adaptors: 

        .#1: Common iterator adaptors: 
            . They are: 
                . back_insert_iterator
                . front_insert_iterator
                . insert_iterator
                . reverse_iterator
            . see iterator_adaptors_01.ixx 

        .#2: Move iterators
            . see iterator_adaptors_02.ixx
            . std::make_move_iterator is a utility that gives us an iterator we can use to move elements from a container to another container.

        .#3: Stream iterators
            . see iterator_adaptors_03.ixx
            . std::istream_iterator and std::ostream_iterator are used to read from and write to streams.


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
    //iterator_adaptors_01_demo();
    iterator_adaptors_03_demo();
}