#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "matrix.h"

/*
    Chapter 16 assignment - Templates, concepts and compile-time computation

    Eight small jobs for the weather station, one idea of the chapter each.
    Write the templates and functions ABOVE main(), and the lines that use them
    in main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Constrain a template with a concept when the exercise asks for it, and
        let the compiler do the checking whenever it can (static_assert).

    matrix.h is the generic Matrix of 16.12, provided for exercise 8.
*/

// Write your templates and functions here, above main().


int main() {

    /*
        Exercise 1 - function templates (16.2)

        Write two function templates:
            T clamped(T value, T low, T high)      keeps value between low and high
            To as(From value)                      static_cast of value to To

        With one T, all three arguments must have the same type, so the third
        line below has to name T. `as` needs its first parameter named by the
        caller, because nothing in the arguments says what To is.

        Sample output:
            clamped(35, 0, 30)         = 30
            clamped(-4.5, 0.0, 30.0)   = 0
            clamped<double>(35, 0, 30) = 30
            as<int>(21.9)              = 21
            as<double>(21)             = 21
    */
    std::println("--- Exercise 1: function templates ---");
    // TODO


    /*
        Exercise 2 - generic lambdas (16.3)

        Write a generic lambda `between` that captures the doubles low = 10 and
        high = 30 by value, and says whether an `auto` value is in [low, high].
        Use it with std::ranges::count_if on a std::vector<int> {5, 15, 25, 35}
        and on a std::vector<double> {12.5, 18.0, 21.5, 40.0}.

        Then write an abbreviated function template (`auto` parameters)
        print_labelled(label, value) that prints "<label>: <value>", and call it
        with a string and with an int and a double.

        Sample output:
            counts between 10 and 30: 2
            temperatures between 10 and 30: 3
            station: north
            7: 21.5
    */
    std::println("\n--- Exercise 2: generic lambdas ---");
    // TODO


    /*
        Exercise 3 - a class template (16.4)

        Write class template Series<T>, a history of values, with:
            a constructor from std::initializer_list<T>    (so the compiler can deduce T)
            void add(const T&)
            std::size_t size() const
            const T& largest() const
            double mean() const

        Make `Series readings{18.5, 24.0, 21.5}` deduce a Series<double>, and
        add the value 3 to a Series<int> {4, 12, 7}.

        Sample output:
            readings: 3 values, largest 24, mean 21.33
            alarms:   4 values, largest 12, mean 6.50
    */
    std::println("\n--- Exercise 3: a class template ---");
    // TODO


    /*
        Exercise 4 - a value as a template parameter (16.5)

        Write class template FixedStack<T, N>: a stack that holds at most N
        values in a std::array, with no heap memory.
            bool push(const T&)              false when the stack is full
            std::optional<T> pop()           the newest value, or std::nullopt when empty
        Add a static_assert that N is greater than 0.

        Push 1, 2, 3, 4 into a FixedStack<int, 3>, then pop four times.

        Sample output:
            push 1: ok
            push 2: ok
            push 3: ok
            push 4: full
            pop: 3
            pop: 2
            pop: 1
            pop: nothing
    */
    std::println("\n--- Exercise 4: a value as a template parameter ---");
    // TODO


    /*
        Exercise 5 - type traits (16.6)

        Write an alias template Narrowest<N>: the smallest of std::uint8_t,
        std::uint16_t, std::uint32_t that can hold N (use std::conditional_t, as
        SmallestIndex did in 16.6). Print sizeof for N = 200, 3000 and 70000, and
        add a static_assert that Narrowest<10> is std::uint8_t (std::is_same_v).

        Then print std::is_integral_v<int>, std::is_integral_v<double> and
        std::is_arithmetic_v<std::string>.

        Sample output:
            Narrowest<200>   is 1 byte(s)
            Narrowest<3000>  is 2 byte(s)
            Narrowest<70000> is 4 byte(s)
            is_integral<int> true, is_integral<double> false, is_arithmetic<std::string> false
    */
    std::println("\n--- Exercise 5: type traits ---");
    // TODO


    /*
        Exercise 6 - concepts (16.7, 16.8)

        Write a concept Measurement: a type with a const member function value()
        whose result converts to double, and a const member function unit()
        whose result converts to std::string_view (use a requires expression with
        compound requirements, as Sensor in 16.8).

        Write struct Temperature {double degrees;} (value() returns degrees, unit()
        returns "C") and struct Humidity {int percent;} (value() returns percent,
        unit() returns a std::string "%"), and an empty struct Broken. Write
        report(const Measurement auto&), printing "<value> <unit>", and a
        static_assert that Temperature and Humidity are Measurements and Broken
        is not.

        Then write two overloads of half(), one for std::integral (value / 2)
        and one for std::floating_point (value * 0.5).

        Sample output:
            21.5 C
            64 %
            half(21) = 10   half(21.0) = 10.5
    */
    std::println("\n--- Exercise 6: concepts ---");
    // TODO


    /*
        Exercise 7 - variadic templates (16.10)

        Write three variadic function templates, each with a fold expression:
            average_of_all(numbers...)   the mean as a double: (0 + ... + numbers), divided by sizeof...
            print_all(args...)           prints every argument followed by a space, then a newline
            all_positive(numbers...)     true if every number is greater than 0

        Sample output:
            average_of_all(1, 2, 3, 4) = 2.5
            print_all: north 21 24.5
            all_positive(3, 1.5, 7)  = true
            all_positive(3, -1, 7)   = false
    */
    std::println("\n--- Exercise 7: variadic templates ---");
    // TODO


    /*
        Exercise 8 - at compile time (16.11, 16.12)

        Write constexpr int sum_of_squares(int upto): 1 + 4 + 9 + ... + upto * upto.
        Check sum_of_squares(4) == 30 with a static_assert, and print it.

        With the provided Matrix: make a constexpr Matrix<int, 2, 2> scale{2, 0, 0, 3},
        compute scale * scale in a constexpr variable, and check with a
        static_assert that its cells are 4, 0, 0 and 9. Print the matrix. (Try
        multiplying scale by a Matrix<int, 3, 3> and read the error.)

        Sample output:
            sum_of_squares(4) = 30
            scale * scale:
              [ 4 0 ]
              [ 0 9 ]
    */
    std::println("\n--- Exercise 8: at compile time ---");
    // TODO

    return 0;
}
