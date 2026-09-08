#include <print>
#include <string>
#include <string_view>

/*
    Chapter 6 assignment - solutions

    Each exercise keeps its full problem statement and sample output in a
    comment above the solution, so this file reads on its own.
*/

// ---------------------------------------------------------------------
// Exercise 1 - is_even and count_evens
//
// Write `bool is_even(int n)` returning true when n is divisible by 2.
// Then, in main, use it in a loop to count how many numbers in the
// range 1..20 are even, and print the count.
//
// Sample output:
//     evens in 1..20: 10
// ---------------------------------------------------------------------
bool is_even(int n) {
    return n % 2 == 0;
}

// ---------------------------------------------------------------------
// Exercise 2 - swap_values (pass by reference)
//
// Write `void swap_values(int& a, int& b)` that exchanges the two
// values through reference parameters.
//
// Sample output:
//     before: x = 3, y = 8
//     after : x = 8, y = 3
// ---------------------------------------------------------------------
void swap_values(int& a, int& b) {
    int temp{a};
    a = b;
    b = temp;
}

// ---------------------------------------------------------------------
// Exercise 3 - describe (default arguments + string_view)
//
// Write `void describe(std::string_view label, int width = 40,
// char fill = '-')` that prints `fill` characters, the label, then
// `fill` characters again, so the whole line is about `width` wide.
//
// Sample output:
//     ---------------- hello ----------------
//     -------- hello --------
//     ======== hello ========
// ---------------------------------------------------------------------
void describe(std::string_view label, int width = 40, char fill = '-') {
    // 2 spaces sit around the label; split the rest between the sides.
    int side{(width - static_cast<int>(label.length()) - 2) / 2};
    if (side < 0) { side = 0; }

    std::string bar(static_cast<std::size_t>(side), fill);
    std::println("{} {} {}", bar, label, bar);
}

// ---------------------------------------------------------------------
// Exercise 4 - area overloads + [[nodiscard]]
//
// Two overloads, both [[nodiscard]]:
//     int area(int side)              -> side * side
//     int area(int width, int height) -> width * height
//
// Sample output:
//     area(5)    = 25
//     area(4, 6) = 24
// ---------------------------------------------------------------------
[[nodiscard]] int area(int side) {
    return side * side;
}

[[nodiscard]] int area(int width, int height) {
    return width * height;
}

// ---------------------------------------------------------------------
// Exercise 5 - sum_to (recursion)
//
// `long sum_to(int n)` returns 1 + 2 + ... + n recursively:
// base case sum_to(0) == 0, recursive step n + sum_to(n - 1).
//
// Sample output:
//     sum_to(1)  = 1
//     sum_to(5)  = 15
//     sum_to(10) = 55
// ---------------------------------------------------------------------
long sum_to(int n) {
    if (n <= 0) {
        return 0;               // base case
    }
    return n + sum_to(n - 1);   // recursive step
}

// ---------------------------------------------------------------------
// Exercise 6 - smallest template + a lambda
//
// `template <typename T> T smallest(T a, T b, T c)` returns the least
// of its three arguments.
//
// Sample output:
//     smallest ints    : 2
//     smallest doubles : 1.1
//     times(6, 7)       : 42
// ---------------------------------------------------------------------
template <typename T>
T smallest(T a, T b, T c) {
    T least{a};
    if (b < least) { least = b; }
    if (c < least) { least = c; }
    return least;
}

int main() {

    // --- Exercise 1 ---
    std::println("--- Exercise 1: is_even ---");
    {
        int evens{0};
        for (int n{1}; n <= 20; ++n) {
            if (is_even(n)) {
                ++evens;
            }
        }
        std::println("evens in 1..20: {}", evens);
    }

    // --- Exercise 2 ---
    std::println("\n--- Exercise 2: swap_values ---");
    {
        int x{3};
        int y{8};
        std::println("before: x = {}, y = {}", x, y);
        swap_values(x, y);
        std::println("after : x = {}, y = {}", x, y);
    }

    // --- Exercise 3 ---
    std::println("\n--- Exercise 3: describe ---");
    {
        describe("hello");                 // defaults: width 40, fill '-'
        describe("hello", 22);             // override width
        describe("hello", 22, '=');        // override width and fill
    }

    // --- Exercise 4 ---
    std::println("\n--- Exercise 4: area overloads ---");
    {
        std::println("area(5)    = {}", area(5));
        std::println("area(4, 6) = {}", area(4, 6));
    }

    // --- Exercise 5 ---
    std::println("\n--- Exercise 5: sum_to ---");
    {
        std::println("sum_to(1)  = {}", sum_to(1));
        std::println("sum_to(5)  = {}", sum_to(5));
        std::println("sum_to(10) = {}", sum_to(10));
    }

    // --- Exercise 6 ---
    std::println("\n--- Exercise 6: smallest + lambda ---");
    {
        std::println("smallest ints    : {}", smallest(7, 2, 5));
        std::println("smallest doubles : {}", smallest(3.4, 1.1, 2.8));

        auto times = [](int a, int b) { return a * b; };
        std::println("times(6, 7)       : {}", times(6, 7));
    }

    return 0;
}
