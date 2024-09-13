/*
    . Topic: 
        . std::vector

    . Highlight the differences between std::vector and std::array. Compare them: 

    std::array

        .Fixed Size:
            The size of std::array is fixed at compile time and cannot be changed.
        Memory Allocation:
            Allocates memory on the stack.
        Performance:
            Generally faster access due to stack allocation and no need for dynamic memory allocation.
        Initialization:
            Can be initialized with a list of values.
        Bound-Checking:
            Provides at() method for bound-checked access; out-of-bounds access using [] is undefined behavior.
        Usage:
            Suitable for fixed-size collections where the size is known at compile time.
        Syntax:
            Requires specifying the size as a template parameter: std::array<int, 5>.
        Iterators:
            Supports iterators for range-based loops and standard algorithms.
        Assignment:
            Supports direct assignment from another std::array of the same type and size.
        Comparison:
            Supports comparison operators (==, !=, <, <=, >, >=).

    std::vector

        Dynamic Size:
            The size of std::vector can be changed at runtime; it can grow and shrink dynamically.
        Memory Allocation:
            Allocates memory on the heap.
        Performance:
            Slightly slower access due to dynamic memory allocation and potential reallocations.
        Initialization:
            Can be initialized with a list of values, default constructor, or by specifying the size.
        Bound-Checking:
            Provides at() method for bound-checked access; out-of-bounds access using [] is undefined behavior.
        Usage:
            Suitable for collections where the size can vary or is not known at compile time.
        Syntax:
            Does not require specifying the size as a template parameter: std::vector<int>.
        Iterators:
            Supports iterators for range-based loops and standard algorithms.
        Assignment:
            Supports direct assignment from another std::vector of the same type.
        Comparison:
            Supports comparison operators (==, !=, <, <=, >, >=).   

    Summary

        Fixed vs. Dynamic:
            Use std::array when the size is fixed and known at compile time.
            Use std::vector when the size can change or is not known at compile time.
        Memory Management:
            std::array uses stack memory, which is faster but limited in size.
            std::vector uses heap memory, which is more flexible but involves dynamic allocation overhead.
        Flexibility:
            std::array is less flexible due to its fixed size.
            std::vector offers more flexibility with its dynamic resizing capabilities.
        Initialization and Usage:
            Both provide convenient initialization and support for iterators and standard algorithms.
        Performance:
            std::array can be slightly faster due to lack of dynamic allocation.
            std::vector can handle varying sizes and is more versatile for general use cases.

    Bottom line: 
        Choosing between std::array and std::vector depends on your specific needs regarding size, performance, and flexibility.
        
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