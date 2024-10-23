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
            . This constructor acts as our default constructor: 
                . BoxContainer(size_t capacity = DEFAULT_CAPACITY);
            . forward iterators allow muliple passes over the same range.
            . you can reset the iterator to the beginning of the range, and expect to get the same values again.
            . they are not single pass
            . algorithm: 
                . std::replace

        .#4: Bidirectional iterators: 
            . see custom_iterators_02.ixx
            . operators: 
                . prefix and post fix operator--
            . algorithms: 
                . std::reverse

        .#5: Random access iteators: 
            . see custom_iterators_05.ixx
            . operators: 
                . operator+(difference_type offset) const
                . operator-(difference_type offset) const
                . operator-(self_type const & other) const
                . operator<(const self_type  & other) const
                . operator>(constself_type & other) const
                . operator<=(const self_type & other) const
                . operator>=(const self_type & other) const
                . operator+=(const difference_type offset)
                . operator-=(const difference_type offset)
                . operator[](const difference_type offset)
                . operator[](const difference_type offset)

        .#6: Custom iterators with views: 
            . see custom_iterators_06.ixx
            . Rationale: When custom containers are powered with iterators, they work seamlesly with standard view types.

        .#7: Constant iterators
            . see custom_iterators_07.ixx

        .#8: Raw pointers as iterators
            . see custom_iterators_08.ixx

        .#9: Wrapping around existing iterators
            . see custom_iterators_09.ixx
             




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
    //custom_iterators_01_demo();
    //custom_iterators_02_demo();
    //custom_iterators_03_demo();
    //custom_iterators_04_demo();
    //custom_iterators_05_demo();
    //custom_iterators_06_demo();
    custom_iterators_07_demo();
    //custom_iterators_08_demo();
    //custom_iterators_09_demo();
}