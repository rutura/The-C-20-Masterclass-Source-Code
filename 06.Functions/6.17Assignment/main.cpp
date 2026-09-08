#include <print>
#include <string>
#include <string_view>

/*
    Chapter 6 assignment - Functions

    Six exercises exercising the tools from this chapter: writing
    functions, declarations vs definitions, pass by value / reference /
    const reference, default arguments, [[nodiscard]] return values,
    overloading, recursion, function templates, and lambdas.

    Use std::print / std::println. Brace-initialize every variable. In
    the sample outputs, text after a ">" is what the user typed (none of
    these exercises need input unless the statement says so).
*/

int main() {

    /*
        Exercise 1 - is_even and count_evens

        Write `bool is_even(int n)` returning true when n is divisible
        by 2. Then, in main, use it in a loop to count how many numbers
        in the range 1..20 are even, and print the count.

        Sample output:
            evens in 1..20: 10
    */
    std::println("--- Exercise 1: is_even ---");
    // TODO


    /*
        Exercise 2 - swap_values (pass by reference)

        Write `void swap_values(int& a, int& b)` that exchanges the two
        values through reference parameters. In main, declare x = 3 and
        y = 8, call swap_values(x, y), and print both before and after.

        Sample output:
            before: x = 3, y = 8
            after : x = 8, y = 3
    */
    std::println("\n--- Exercise 2: swap_values ---");
    // TODO


    /*
        Exercise 3 - describe (default arguments + string_view)

        Write `void describe(std::string_view label, int width = 40,
        char fill = '-')` that prints `label` centred-ish by printing
        `fill` characters, then the label, then `fill` characters again,
        so the whole line is about `width` characters wide. Call it once
        with just a label, once overriding width, once overriding both.

        Sample output (exact padding may vary with your formula):
            ---------------- hello ----------------
            -------- hello --------
            ======== hello ========
    */
    std::println("\n--- Exercise 3: describe ---");
    // TODO


    /*
        Exercise 4 - area overloads + [[nodiscard]]

        Write two overloads, both marked [[nodiscard]]:
            int area(int side)              -> side * side
            int area(int width, int height) -> width * height
        Call each and print the results. (You do not have to demonstrate
        the compiler warning, just write the [[nodiscard]] correctly.)

        Sample output:
            area(5)    = 25
            area(4, 6) = 24
    */
    std::println("\n--- Exercise 4: area overloads ---");
    // TODO


    /*
        Exercise 5 - sum_to (recursion)

        Write `long sum_to(int n)` that returns 1 + 2 + ... + n using
        recursion: base case sum_to(0) == 0, recursive step
        n + sum_to(n - 1). Print sum_to(1), sum_to(5) and sum_to(10).

        Sample output:
            sum_to(1)  = 1
            sum_to(5)  = 15
            sum_to(10) = 55
    */
    std::println("\n--- Exercise 5: sum_to ---");
    // TODO


    /*
        Exercise 6 - smallest template + a lambda

        Write `template <typename T> T smallest(T a, T b, T c)` that
        returns the least of its three arguments. Call it with three
        ints and three doubles.

        Then declare a lambda `auto times = [](int a, int b){ return a * b; };`
        and print times(6, 7).

        Sample output:
            smallest ints    : 2
            smallest doubles : 1.1
            times(6, 7)       : 42
    */
    std::println("\n--- Exercise 6: smallest + lambda ---");
    // TODO

    return 0;
}
