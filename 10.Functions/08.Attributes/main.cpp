/*
    . Attributes: 
        . Attributes in C++ are a powerful way to communicate extra information to the compiler without affecting the behavior of the program directly. Attributes from earlier standards like [[noreturn]], [[deprecated]], and [[nodiscard]] help with code readability, diagnostics, and error prevention. Newer attributes in C++20 ([[likely]], [[no_unique_address]]) and C++23 ([[assume]], [[nodiscard("reason")]]) focus on further improving performance and providing clearer guidance.

        . Attributes make C++ code cleaner, more maintainable, and more optimized, and understanding when to use them helps write better software.

        . Compilers have varying levels of support for these attributes.

    . Uses vcpkg as a dependency manager
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Note: 
            . There are other ways to build but we'll focus on these two in the course.
            . You can use the docker containers that come with the course for a fully reproducible build environment.
                . one for gcc 14 [link]
                . one for clang 18 [link]

    . Requirements:
        . A modern C++ compiler: 
            . eg: gcc 14, clang 16 or latest msvc. 
        . cmake 3.30 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
            . how to update vcpkg: https://learn.microsoft.com/en-us/vcpkg/about/faq#how-do-i-update-vcpkg
        . A debugger: 
            . eg: gdb, lldb, or the visual studio debugger
        . Goood to have: 
            . Git

        . Editor: 
            . VS Code: 
                . The C++ extension
                . The CMake Tools extension
                . The CMake extension
                . NOTE: These are required to give you the best experience.

        . Know where a binary is: 
            . Linux: which command
                . eg: which ninja
            . Windows: Get-command
                . eg: Get-command ninja

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
#include <fmt/format.h>
#include <cstdlib>

// [[noreturn]] (C++11)  tells the compiler that a function will not return 
// control to the caller. It can be useful in functions that terminate the program or throw exceptions.
//This is useful when writing functions that handle fatal errors or terminate the program.
// The compiler will generate warnings if any code after a [[noreturn]] function is treated as reachable.
[[noreturn]] void exit_program() {
    std::exit(1);  // Exits the program without returning
}


//[[deprecated]] (Introduced in C++11, but C++14 added the ability to provide a message)
//Indicates that a function, class, or variable is deprecated, warning the user that the feature should not be used anymore. When updating libraries, marking old APIs as deprecated alerts users without breaking code immediately.
[[deprecated("Use new_function() instead")]]
void old_function() {
    fmt::println("This is the old function.");
}

void new_function() {
    fmt::println("This is the new function.");
}


//[[nodiscard]] (C++17)
//This attribute warns the user if the return value of a function is discarded. It's useful for functions where the return value should not be ignored, such as error codes. Helps catch logical errors in cases where ignoring a return value could result in bugs, e.g., ignoring error codes in functions.
[[nodiscard]] int calculate_value() {
    return 42;
}

//[[fallthrough]]
//In a switch statement, this attribute tells the compiler that falling through to the next case is intentional.
//If the attribute is not present, the compiler will generate a warning (or an error, depending on the compiler and settings) if a case falls through to the next one without a break statement. When designing finite state machines or complex control structures with switch, this attribute ensures readability and prevents unintentional fallthrough.

void handle_switch(int value) {
    switch (value) {
        case 1:
            fmt::println("Handling 1");
            //[[fallthrough]];
        case 2:
            fmt::println("Handling 2");
            break;
        default:
            fmt::println("Handling default");
    }
}


//[[likely]] and [[unlikely]]   (C++20)
//These attributes indicate to the compiler the expected code execution path, potentially improving branch prediction. Optimizing performance-critical code where certain branches are more probable than others, such as handling errors in large input sets.

int process_value(int value) {
    if (value == 42) [[likely]] {
        return value * 2;
    } else [[unlikely]] {
        return value / 2;
    }
}

//[[assume]]  (C++23) //This attribute allows programmers to inform the compiler that a certain condition will always hold. The compiler can then make optimizations based on this assumption, but if the condition fails, the behavior is undefined. Use this attribute in highly performance-sensitive code where you want to help the compiler optimize based on known truths.
void process_data(int value) {
    [[assume(value > 0)]];
    fmt::println("Value is greater than 0: {}", value);
}


// [[nodiscard("Use the return value to check for errors")]] . C++23 adds the ability to provide a message with [[nodiscard]] to give more context to the warning. This can be useful for explaining why the return value should not be ignored.
[[nodiscard("This result must be used for important logic.")]]
int compute_important_value() {
    return 100;
}


import utilities;

int main() {

    //[[noretun]] 
    /*
    fmt::println("Exiting the program");
    exit_program();// This call may not return
    fmt::println("Program ends properly");
    */


    //[[deprecated]]
    /*
    old_function(); // This will generate a warning
    new_function(); // This will not generate a warning
    */

    //[[nodiscard]]
    /*
    calculate_value(); // This will generate a warning
    int result = calculate_value(); // This will not generate a warning
    */


    //[[fallthrough]]
    /*
    handle_switch(1);
    */

    //[[likely]] and [[unlikely]]
    /*
    auto value1 = process_value(42);
    auto value2 = process_value(43);
    fmt::println("Value1: {}, Value2: {}", value1, value2);
    */

    //[[assume]] 
    /*
    process_data(5);
    */


    //[[nodiscard]] with message
    /*
    compute_important_value();
    */
}