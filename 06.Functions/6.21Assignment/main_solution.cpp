#include <cmath>
#include <print>
#include <random>
#include <string>

/*
    Chapter 6 assignment - solutions

    Each exercise keeps its full problem statement and sample output in a
    comment above the solution, so this file reads on its own.
*/

// ---------------------------------------------------------------------
// Exercise 1 - hypotenuse (prototype + math library)
//
// Prototype above main, definition after main. Returns
// sqrt(a*a + b*b) using std::sqrt.
//
// Sample output:
//     hypotenuse(3, 4)  = 5
//     hypotenuse(5, 12) = 13
// ---------------------------------------------------------------------
double hypotenuse(double a, double b);   // prototype

// ---------------------------------------------------------------------
// Exercise 3 - call counter (static local)
//
// void announce() prints "call number N" where N counts calls via a
// static local.
//
// Sample output:
//     call number 1
//     call number 2
//     call number 3
//     call number 4
// ---------------------------------------------------------------------
void announce() {
    static int calls{0};
    ++calls;
    std::println("call number {}", calls);
}

// ---------------------------------------------------------------------
// Exercise 4 - to_minutes_seconds (reference parameters)
//
// Splits total seconds into whole minutes and leftover seconds, written
// through reference parameters.
//
// Sample output:
//     200 seconds = 3 min 20 sec
// ---------------------------------------------------------------------
void to_minutes_seconds(int total, int& minutes, int& seconds) {
    minutes = total / 60;
    seconds = total % 60;
}

// ---------------------------------------------------------------------
// Exercise 5a - line (default arguments)
//
// Prints `width` copies of `fill`, then a newline. Defaults width 20,
// fill '-'.
//
// Sample output:
//     --------------------
//     **********
//     ==============
// ---------------------------------------------------------------------
void line(int width = 20, char fill = '-') {
    std::println("{}", std::string(static_cast<std::size_t>(width), fill));
}

// ---------------------------------------------------------------------
// Exercise 5b - max3 (function template)
//
// Returns the largest of three values.
//
// Sample output:
//     max3 ints    : 9
//     max3 doubles : 4.4
// ---------------------------------------------------------------------
template <typename T>
T max3(T a, T b, T c) {
    T largest{a};
    if (b > largest) { largest = b; }
    if (c > largest) { largest = c; }
    return largest;
}

// ---------------------------------------------------------------------
// Exercise 6a - power (recursion, [[nodiscard]])
//
// base^exp: base case power(base, 0) == 1, step base * power(base, exp-1).
//
// Sample output:
//     power(2, 10) = 1024
//     power(5, 3)  = 125
// ---------------------------------------------------------------------
[[nodiscard]] long power(int base, int exp) {
    if (exp <= 0) {
        return 1;                       // base case
    }
    return base * power(base, exp - 1); // recursive step
}

int main() {

    // --- Exercise 1 ---
    std::println("--- Exercise 1: hypotenuse ---");
    {
        std::println("hypotenuse(3, 4)  = {}", hypotenuse(3, 4));
        std::println("hypotenuse(5, 12) = {}", hypotenuse(5, 12));
    }

    // --- Exercise 2: roll histogram ---
    std::println("\n--- Exercise 2: roll histogram ---");
    {
        std::random_device rd{};
        std::default_random_engine engine{rd()};
        std::uniform_int_distribution<int> die{1, 6};

        int counts[7]{};                    // index 1..6 used
        for (int i{0}; i < 60; ++i) {
            ++counts[die(engine)];
        }
        for (int face{1}; face <= 6; ++face) {
            std::println("{}: {}", face, counts[face]);
        }
    }

    // --- Exercise 3 ---
    std::println("\n--- Exercise 3: call counter ---");
    {
        announce();
        announce();
        announce();
        announce();
    }

    // --- Exercise 4 ---
    std::println("\n--- Exercise 4: to_minutes_seconds ---");
    {
        int minutes{};
        int seconds{};
        to_minutes_seconds(200, minutes, seconds);
        std::println("200 seconds = {} min {} sec", minutes, seconds);
    }

    // --- Exercise 5 ---
    std::println("\n--- Exercise 5: line + max3 ---");
    {
        line();               // defaults
        line(10, '*');        // both
        line(14, '=');        // both
        std::println("max3 ints    : {}", max3(4, 9, 2));
        std::println("max3 doubles : {}", max3(1.1, 4.4, 3.3));
    }

    // --- Exercise 6 ---
    std::println("\n--- Exercise 6: power + lambda ---");
    {
        std::println("power(2, 10) = {}", power(2, 10));
        std::println("power(5, 3)  = {}", power(5, 3));

        auto apply_twice = [](int n) { return n + n; };
        std::println("apply_twice(21) = {}", apply_twice(21));
    }

    return 0;
}

// Exercise 1 definition, after main.
double hypotenuse(double a, double b) {
    return std::sqrt(a * a + b * b);
}
