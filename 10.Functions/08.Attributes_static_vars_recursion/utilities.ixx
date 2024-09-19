module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import attributes;
import recursion;

export void attributes_demo(){

    //[[noretun]] 
    /*
    fmt::println("Exiting the program");
    attributes::exit_program();// This call may not return
    fmt::println("Program ends properly");
    */


    //[[deprecated]]
    /*
    attributes::old_function(); // This will generate a warning
    attributes::new_function(); // This will not generate a warning
    */

    //[[nodiscard]]
    /*
    attributes::calculate_value(); // This will generate a warning
    int result = attributes::calculate_value(); // This will not generate a warning
    */


    //[[fallthrough]]
    /*
    attributes::handle_switch(1);
    */

    //[[likely]] and [[unlikely]]
    /*
    auto value1 = attributes::process_value(42);
    auto value2 = attributes::process_value(43);
    fmt::println("Value1: {}, Value2: {}", value1, value2);
    */

    //[[assume]] 
    /*
    attributes::process_data(5);
    */


    //[[nodiscard]] with message
    /*
    attributes::compute_important_value();
    */

}


export void recursion_demo(){
    //Recursion
    int result = recursion::fibonacci(10);
    fmt::println("Fibonacci of 10 is: {}", result);

    //Memoization
    result = recursion::fibonacci_memo(10);
    fmt::println("Fibonacci of 10 is: {}", result);

    //Iterative
    result = recursion::fibonacci_iterative(10);
    fmt::println("Fibonacci of 10 is: {}", result);

    //Recursive lambdas (C++ 23)
    //Failed attempt
    /*
        auto fibonacci_lambda = [](int n) {
        if (n < 2) { return n; }
        return fibonacci_lambda(n -1) + fibonacci_lambda(n -2);  // Compiler error!
    };
    */
    auto fibonacci_lambda = [](this auto& self, int n) {
        if (n < 2) { return n; }
        return self(n -1) + self(n -2);
    };

    auto value = fibonacci_lambda(10);
    fmt::println("Fibonacci of 10 is: {}", value);
}
