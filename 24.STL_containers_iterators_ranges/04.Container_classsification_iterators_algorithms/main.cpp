/*
    . Container classification and container specific iterators: 
        .#1: Classification
            . Sequence containers: vector, list, deque, forward_list, array
            . Associative containers: set, multiset, map, multimap
            . Unordered associative containers: unordered_set, unordered_multiset, unordered_map, unordered_multimap
            . Container adaptors: stack, queue, priority_queue


            IMPORTANT NOTE:   Once you see a container, ask your self what kind of iterator it provides. 
                              This will help you understand what kind of algorithms you can use with that container.

        .#2: Container specific iterators
            . vector: random access iterator
            . list: bidirectional iterator
            . deque: random access iterator
            . forward_list: forward iterator
            . array: random access iterator
            . set: bidirectional iterator
            . multiset: bidirectional iterator
            . map: bidirectional iterator
            . multimap: bidirectional iterator
            . unordered_set: forward iterator
            . unordered_multiset: forward iterator
            . unordered_map: forward iterator
            . unordered_multimap: forward iterator
            . stack: no iterator
            . queue: no iterator
            . priority_queue: no iterator

        .#3: Container, algorithms and iterator examples.
            . Show examples only for sequence containers showing: 
                . containers,
                . the iterators they provide
                . algorithms that use the iterators
                . adding iterator requirements to your functions. The print function is a good example.
            . Can't show all the options. The goal is to have an overview and be able to use the docs when you need to.
            . Show the code for just associative containers and leave the rest as a research exercise.
            . But do show a proper classification of the containers, algorithms (common ones) and iterators.
            . Brush up on container performance and algorithms complexity. (Leave heavy details for the DSA course)



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
        . gcc
        . cmake
        . ninja
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

*/

// One line comment
#include "utilities.h"

int main() {
    //containers_iterators_algorithms_01_demo();
    containers_iterators_algorithms_02_demo();
}