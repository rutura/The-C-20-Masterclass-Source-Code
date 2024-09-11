/*
    . Exploring sequences of characters: strings
    . Topics: 
        .  Basic Declaration and Initialization: Shows how to declare and initialize std::string.
        . Using Constructors: Demonstrates different ways to create std::string using constructors.
        . Accessing Characters: Accessing individual characters using [] and at().
        . Modifying Strings: Modifying characters in the string.
        . Appending and Concatenation: Appending and concatenating strings.
        . Substrings: Extracting substrings.
        . Finding Substrings: Finding substrings within a string.
        . Comparison: Comparing strings using compare().
        . Inserting and Erasing: Inserting and erasing parts of a string.
        . Length and Capacity: Getting the length and capacity of a string.
        . Iterating over a string: Iterating over a string using a range-based for loop.
        . Clearing a string: Clearing the contents of as string.

    . Comparisons to std::array and std::vector: 
        std::string
            Type:
                Specialized for handling sequences of characters.
            Fixed/Dynamic Size:
                Dynamic size, can grow and shrink as needed.
            Memory Allocation:
                Allocates memory on the heap.
            Element Type:
                Always char.
            Initialization:
                Initialized with C-strings, copy constructors, substrings, etc.
            Usage:
                Specifically designed for text manipulation and string operations.
            Methods:
                Rich set of methods for string manipulation (e.g., substr(), find(), insert(), erase()).
            Performance:
                Optimized for common string operations; may include small string optimization.
            Comparison:
                Supports lexicographical comparison.

        std::array

            Type:
                Generic fixed-size array.
            Fixed/Dynamic Size:
                Fixed size determined at compile time.
            Memory Allocation:
                Allocates memory on the stack.
            Element Type:
                Can hold any type of elements.
            Initialization:
                Requires size as a template parameter; can be initialized with a list of values.
            Usage:
                Suitable for fixed-size collections known at compile time.
            Methods:
                Limited methods compared to std::vector and std::string (e.g., fill(), swap()).
            Performance:
                Faster access due to stack allocation.
            Comparison:
                Supports element-wise comparison.

        std::vector

            Type:
                Generic dynamic-size array.
            Fixed/Dynamic Size:
                Dynamic size, can grow and shrink as needed.
            Memory Allocation:
                Allocates memory on the heap.
            Element Type:
                Can hold any type of elements.
            Initialization:
                Initialized with a list of values, size, and default values.
            Usage:
                Suitable for collections where the size can vary.
            Methods:
                Rich set of methods for array manipulation (e.g., push_back(), pop_back(), insert(), erase()).
            Performance:
                Slightly slower due to dynamic memory management.
            Comparison:
                Supports element-wise comparison.

        Summary

            Specialization:
                std::string is specialized for character sequences and text manipulation.
                std::array is for fixed-size collections known at compile time.
                std::vector is for dynamic-size collections that can grow and shrink.
            Memory Management:
                std::string and std::vector use heap allocation.
                std::array uses stack allocation.
            Flexibility:
                std::string and std::vector offer dynamic resizing.
                std::array is fixed in size and cannot be resized.
            Element Type:
                std::string is restricted to char elements.
                std::array and std::vector can hold any type of elements.
            Usage Scenarios:
                Use std::string for text manipulation.
                Use std::array for fixed-size, efficient collections.
                Use std::vector for flexible, dynamic collections.

        This comparison highlights the specific use cases and characteristics of each container type, helping you choose the appropriate one based on your requirements.
    
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