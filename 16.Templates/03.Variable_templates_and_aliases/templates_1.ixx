/*
    . Exploring variable templates: We see a few examples.

        . Basic Example: Variable Templates for Constants
            . Define constants like pi for different types.
            . Example: template<typename T> constexpr T pi = T(3.14159);
        . Type Traits with Variable Templates
            . Simplify type trait checks like std::is_integral.
            . Example: template<typename T> constexpr bool is_integral_v = std::is_integral<T>::value;
        . Generic Values with Specialization
            . Use variable templates to provide default values for different types, with specializations.
            . Example: template<> constexpr int default_value<int> = 42;
        . Compile-time Computation with constexpr
            . Compute values like factorials at compile-time using variable templates.
            . Example: template<int N> constexpr int factorial = N * factorial<N - 1>;
*/
module;

#include <fmt/format.h>

#include <type_traits>

export module templates_1;

namespace templates_1{

    //#1: A simple constant for Pi that works with different types
    export template<typename T>
    constexpr T PI = T(3.1415926535897932385);

    //#2: A variable template that simplifies checking if a type is integral
    template<typename T>
    constexpr bool is_integral_v = std::is_integral<T>::value;

    export void check_integer(){
        // Testing with different types
        fmt::println("Is int integral? {}", is_integral_v<int>);           // true
        fmt::println("Is double integral? {}", is_integral_v<double>);     // false
        fmt::println("Is char integral? {}", is_integral_v<char>);         // true
        fmt::println("Is float integral? {}", is_integral_v<float>);       // false

        //Doing it raw
        fmt::println("Is int integral? {}", std::is_integral<int>::value);      // true
        fmt::println("Is double integral? {}", std::is_integral<double>::value); // false
        fmt::println("Is char integral? {}", std::is_integral<char>::value);    // true
        fmt::println("Is float integral? {}", std::is_integral<float>::value);  // false

    }

    //#3: Generic default value for different types
    template<typename T>
    constexpr T default_value = T{};

    // Specializations for specific types. Yes, variable templates can be specialized.
    // DO THIS: Comment out the specializations and see what happens.
    template<>
    constexpr int default_value<int> = 42;

    template<>
    constexpr const char* default_value<const char*> = "Hello, world!";

    export void print_default_values(){
        fmt::println("Default value for int: {}", default_value<int>);
        fmt::println("Default value for double: {}", default_value<double>);
        fmt::println("Default value for char: {}", default_value<char>);
        fmt::println("Default value for float: {}", default_value<float>);
        fmt::println("Default value for const char*: {}", default_value<const char*>);
    }

    // #4: Compute the factorial at compile-time using a variable template
    export template<int N>
    constexpr int factorial = N * factorial<N - 1>;

    template<>
    constexpr int factorial<0> = 1;
    
} // namespace templates_1