/*
    . Custom container iterators: 

        .#1: Input iterator
            . see custom_iterators_01.ixx 
            . Input iterators are single pass iterators.

        .#2: Output iterator
            . see custom_iterators_01.ixx
            . the same code from custom_iterators_01.ixx is used here.
            . operator* and operator-> are used to modify the value referenced by the iterator.
            . hence, this being an output iterator, we can use to modify the value referenced by the iterator.

        .#3: Forward iterator
            . see custom_iterators_01.ixx
            . the same code from custom_iterators_01.ixx is used here.
            . The special requirement for forward iterators is to have a default constructor.
            . forward iterators allow muliple passes over the same range.
            . you can reset the iterator to the beginning of the range, and expect to get the same values again.



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
    custom_iterators_01_demo();
    //custom_iterators_02_demo();
}