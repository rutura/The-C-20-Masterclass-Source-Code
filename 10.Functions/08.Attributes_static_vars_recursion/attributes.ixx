module;

#include <fmt/format.h>
#include <cstdlib>

export module attributes;

namespace attributes{

    // [[noreturn]] (C++11)  tells the compiler that a function will not return 
    // control to the caller. It can be useful in functions that terminate the program or throw exceptions.
    //This is useful when writing functions that handle fatal errors or terminate the program.
    // The compiler will generate warnings if any code after a [[noreturn]] function is treated as reachable.
    export [[noreturn]] void exit_program() {
        std::exit(1);  // Exits the program without returning
    }


    //[[deprecated]] (Introduced in C++11, but C++14 added the ability to provide a message)
    //Indicates that a function, class, or variable is deprecated, warning the user that the feature should not be used anymore. When updating libraries, marking old APIs as deprecated alerts users without breaking code immediately.
    export [[deprecated("Use new_function() instead")]]
    void old_function() {
        fmt::println("This is the old function.");
    }

    export void new_function() {
        fmt::println("This is the new function.");
    }


    //[[nodiscard]] (C++17)
    //This attribute warns the user if the return value of a function is discarded. It's useful for functions where the return value should not be ignored, such as error codes. Helps catch logical errors in cases where ignoring a return value could result in bugs, e.g., ignoring error codes in functions.
    export [[nodiscard]] int calculate_value() {
        return 42;
    }

    //[[fallthrough]]
    //In a switch statement, this attribute tells the compiler that falling through to the next case is intentional.
    //If the attribute is not present, the compiler will generate a warning (or an error, depending on the compiler and settings) if a case falls through to the next one without a break statement. When designing finite state machines or complex control structures with switch, this attribute ensures readability and prevents unintentional fallthrough.

    export void handle_switch(int value) {
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

    export int process_value(int value) {
        if (value == 42) [[likely]] {
            return value * 2;
        } else [[unlikely]] {
            return value / 2;
        }
    }

    //[[assume]]  (C++23) //This attribute allows programmers to inform the compiler that a certain condition will always hold. The compiler can then make optimizations based on this assumption, but if the condition fails, the behavior is undefined. Use this attribute in highly performance-sensitive code where you want to help the compiler optimize based on known truths.
    export void process_data(int value) {
        [[assume(value > 0)]];
        fmt::println("Value is greater than 0: {}", value);
    }


    // [[nodiscard("Use the return value to check for errors")]] . C++23 adds the ability to provide a message with [[nodiscard]] to give more context to the warning. This can be useful for explaining why the return value should not be ignored.
    export [[nodiscard("This result must be used for important logic.")]]
    int compute_important_value() {
        return 100;
    }
    
} // namespace attributes