#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>
#include <print>
#include <string_view>

// 6.10 introduced constexpr variables and functions. A constexpr function can
// run while the program is being COMPILED, when its arguments are known then,
// and the answer becomes part of the executable. Computing at compile time is
// what "metaprogramming" means in C++: the program writes parts of itself.

// ---------------------------------------------------------------------------
// 1. The old way: a template that computes. Recursion through instantiation,
//    stopped by a specialization (16.9). It works, and it is hard to read.
// ---------------------------------------------------------------------------
template <unsigned N>
struct Factorial {
    static constexpr unsigned long long value{N * Factorial<N - 1>::value};
};

template <>
struct Factorial<0> {
    static constexpr unsigned long long value{1};
};

// ---------------------------------------------------------------------------
// 2. The modern way: an ordinary function, marked constexpr. Loops, local
//    variables and calls to other constexpr functions are all allowed.
// ---------------------------------------------------------------------------
constexpr unsigned long long factorial(unsigned n) {
    unsigned long long result{1};
    for (unsigned i{2}; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// A constexpr function can build a whole TABLE at compile time.
// Here: Fahrenheit for every Celsius degree from 0 to 40.
constexpr std::array<double, 41> make_fahrenheit_table() {
    std::array<double, 41> table{};
    for (std::size_t celsius{0}; celsius < table.size(); ++celsius) {
        table[celsius] = static_cast<double>(celsius) * 9.0 / 5.0 + 32.0;
    }
    return table;
}

// The standard algorithms are constexpr too (since C++20).
constexpr int sum_of_squares(int upto) {
    std::array<int, 10> values{};
    std::iota(values.begin(), values.begin() + upto, 1);                 // 1, 2, 3 ...
    int total{0};
    for (int i{0}; i < upto; ++i) {
        total += values[static_cast<std::size_t>(i)] * values[static_cast<std::size_t>(i)];
    }
    return total;
}

// A class can be constexpr as well: a constructor and member functions
// that may run at compile time.
class Celsius {
public:
    constexpr explicit Celsius(double degrees) : degrees_{degrees} {}
    constexpr double fahrenheit() const { return degrees_ * 9.0 / 5.0 + 32.0; }
    constexpr bool freezing() const { return degrees_ <= 0.0; }

private:
    double degrees_;
};

// ---------------------------------------------------------------------------
// 3. consteval: the function MUST run at compile time. A call whose arguments
//    are not known then is an error. Good for checking a setting early.
// ---------------------------------------------------------------------------
consteval std::size_t slots_for(int hours, int readings_per_hour) {
    if (hours <= 0 || readings_per_hour <= 0) {
        throw "hours and readings per hour must be positive";            // in consteval, a throw is a compile error
    }
    return static_cast<std::size_t>(hours * readings_per_hour);
}

// ---------------------------------------------------------------------------
// 4. if consteval (C++23): different code when the function is being
//    evaluated at compile time or at run time.
// ---------------------------------------------------------------------------
constexpr std::string_view where_am_i() {
    if consteval {
        return "compile time";
    } else {
        return "run time";
    }
}

// ---------------------------------------------------------------------------
// 5. constinit: initialized at compile time, but NOT constant: it can change
//    later. It guarantees there is no dynamic initialization to run before
//    main(), for a variable that lives for the whole program.
// ---------------------------------------------------------------------------
constinit int readings_taken{0};

int main() {

    std::println("--- the old way and the new way");
    std::println("Factorial<10>::value = {}", Factorial<10>::value);        // computed by the compiler
    std::println("factorial(10)         = {}", factorial(10));
    constexpr unsigned long long at_compile_time{factorial(10)};            // forced to be computed now
    static_assert(at_compile_time == 3'628'800);
    static_assert(Factorial<5>::value == factorial(5));                     // both ways agree, checked while compiling

    std::println("\n--- a table made by the compiler");
    constexpr auto table{make_fahrenheit_table()};
    static_assert(table[0] == 32.0 && table[100 / 10] == 50.0);             // checked while compiling
    std::println("0 C = {} F   20 C = {} F   40 C = {} F", table[0], table[20], table[40]);

    std::println("\n--- standard algorithms and classes at compile time");
    static_assert(sum_of_squares(3) == 14);                                 // 1 + 4 + 9
    constexpr Celsius boiling_point{100.0};
    constexpr Celsius frost{-5.0};
    static_assert(boiling_point.fahrenheit() == 212.0);
    std::println("sum_of_squares(4) = {}   100 C = {} F   -5 C freezing: {}",
                 sum_of_squares(4), boiling_point.fahrenheit(), frost.freezing());

    // The same functions work at run time with run-time arguments.
    int degrees{0};
    for (int value : {12, 18, 24}) {
        degrees += value;
    }
    std::println("run time: Celsius{{{}}}.fahrenheit() = {}", degrees, Celsius{static_cast<double>(degrees)}.fahrenheit());

    std::println("\n--- consteval");
    constexpr std::size_t slots{slots_for(24, 4)};                          // 96 readings a day
    std::array<double, slots> day{};                                        // so the size is a constant, checked
    std::println("slots_for(24, 4) = {}   a day of readings holds {}", slots, day.size());
    // slots_for(0, 4);                          // error at compile time: the throw is evaluated by the compiler
    // slots_for(degrees, 4);                    // error: degrees is not known at compile time

    std::println("\n--- if consteval");
    constexpr std::string_view during_compile{where_am_i()};
    std::println("a constant:      {}", during_compile);
    std::println("a normal call:   {}", where_am_i());

    std::println("\n--- constinit");
    ++readings_taken;
    ++readings_taken;
    std::println("readings_taken = {} (started at 0 without any code running at start-up)", readings_taken);
    // constexpr int fixed{0};  ++fixed;         // error: constexpr means constant
    // constinit is for a variable that is set at compile time and then CHANGES.
    //
    //    const        never changes after initialization (may be set at run time)
    //    constexpr    never changes, and its value is known at compile time
    //    consteval    a function that can only run at compile time
    //    constinit    changes later, but its first value is known at compile time
    return 0;
}
