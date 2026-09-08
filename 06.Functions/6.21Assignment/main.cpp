#include <cmath>
#include <print>
#include <random>

/*
    Chapter 6 assignment - Functions

    Six exercises drawn only from this chapter: prototypes and
    definitions, the math library, random numbers, scope and static
    locals, reference parameters, default arguments, overloading,
    templates, recursion, [[nodiscard]], and lambdas.

    Use std::print / std::println. Brace-initialize every variable. In
    the sample outputs, text after a ">" is what the user typed.
*/

int main() {

    /*
        Exercise 1 - hypotenuse (prototype + math library)

        Declare a prototype `double hypotenuse(double a, double b);`
        above main and define it AFTER main. It returns
        sqrt(a*a + b*b) using std::sqrt. Call it with (3, 4) and
        (5, 12) and print the results.

        Sample output:
            hypotenuse(3, 4)  = 5
            hypotenuse(5, 12) = 13
    */
    std::println("--- Exercise 1: hypotenuse ---");
    // TODO


    /*
        Exercise 2 - roll histogram (random numbers)

        Seed a std::default_random_engine from std::random_device. Make a
        uniform_int_distribution<int>{1, 6}. Roll it 60 times, counting
        how many of each face (1..6) came up, then print the six counts.
        (The exact numbers vary run to run; they should sum to 60.)

        Sample output (numbers will differ):
            1: 9
            2: 12
            3: 8
            4: 11
            5: 10
            6: 10
    */
    std::println("\n--- Exercise 2: roll histogram ---");
    // TODO


    /*
        Exercise 3 - call counter (static local)

        Write `void announce();` that prints "call number N" where N is 1
        on the first call, 2 on the second, and so on - using a static
        local counter. Call it four times from main.

        Sample output:
            call number 1
            call number 2
            call number 3
            call number 4
    */
    std::println("\n--- Exercise 3: call counter ---");
    // TODO


    /*
        Exercise 4 - to_minutes_seconds (reference parameters)

        Write `void to_minutes_seconds(int total, int& minutes,
        int& seconds)` that splits a total number of seconds into whole
        minutes and leftover seconds, writing both through the reference
        parameters. Call it with 200 and print the two results.

        Sample output:
            200 seconds = 3 min 20 sec
    */
    std::println("\n--- Exercise 4: to_minutes_seconds ---");
    // TODO


    /*
        Exercise 5 - line (default arguments) + max3 (template)

        (a) Write `void line(int width = 20, char fill = '-');` that
            prints `width` copies of `fill` followed by a newline. Call
            it once with no arguments, once with just a width, once with
            both.

        (b) Write `template <typename T> T max3(T a, T b, T c);` that
            returns the largest of three values. Call it with three ints
            and three doubles.

        Sample output:
            --------------------
            **********
            ==============
            max3 ints    : 9
            max3 doubles : 4.4
    */
    std::println("\n--- Exercise 5: line + max3 ---");
    // TODO


    /*
        Exercise 6 - power (recursion, [[nodiscard]]) + a lambda

        (a) Write `[[nodiscard]] long power(int base, int exp)` that
            computes base^exp recursively: base case power(base, 0) == 1,
            recursive step base * power(base, exp - 1). Print power(2, 10)
            and power(5, 3).

        (b) Declare a lambda `auto apply_twice = [](int n){ return n + n; };`
            and print apply_twice(21).

        Sample output:
            power(2, 10) = 1024
            power(5, 3)  = 125
            apply_twice(21) = 42
    */
    std::println("\n--- Exercise 6: power + lambda ---");
    // TODO

    return 0;
}
