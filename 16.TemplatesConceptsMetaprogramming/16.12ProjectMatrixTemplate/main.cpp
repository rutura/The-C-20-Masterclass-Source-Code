#include <numeric>
#include <print>
#include <type_traits>

#include "matrix.h"

// A tour of the generic Matrix. Read matrix.h first: every feature in it was
// introduced in this chapter or in chapter 12.

// Fibonacci numbers from matrix multiplication. The matrix
//     [ 1 1 ]
//     [ 1 0 ]
// raised to the power n has the n-th Fibonacci number in its corner. The
// function is constexpr, so the compiler can run it.
constexpr long long fibonacci(int n) {
    Matrix<long long, 2, 2> step{1, 1, 1, 0};
    auto result{Matrix<long long, 2, 2>::identity()};
    for (int i{0}; i < n; ++i) {
        result = result * step;
    }
    return result[0, 1];
}

int main() {

    // Three stations, four readings each (at 6, 12, 18 and 24 hours).
    Matrix<double, 3, 4> readings{
        11.5, 18.5, 15.0, 12.0,       // north
        14.0, 24.0, 20.5, 16.5,       // south
        12.5, 21.5, 17.0, 13.0};      // east
    std::println("readings, {} stations x {} readings:\n{:6.1f}", readings.rows(), readings.columns(), readings);

    // A weighted average per station is a matrix product: (3 x 4) times (4 x 1) is (3 x 1).
    // The midday readings count most.
    Matrix<double, 4, 1> weights{0.1, 0.4, 0.4, 0.1};
    auto weighted{readings * weights};
    std::println("\nweighted average per station, {} x {}:\n{:6.2f}", weighted.rows(), weighted.columns(), weighted);

    // The type of the result was worked out by the compiler from the two shapes.
    static_assert(std::is_same_v<decltype(weighted), Matrix<double, 3, 1>>);

    auto by_hour{readings.transposed()};                         // Matrix<double, 4, 3>
    std::println("\nthe same readings by hour, {} x {}:\n{:6.1f}", by_hour.rows(), by_hour.columns(), by_hour);

    // The cells form a range, so the algorithms of chapter 15 work on a matrix.
    double total{std::accumulate(readings.begin(), readings.end(), 0.0)};
    std::println("\nall readings added up: {}", total);

    // Operators, as in chapter 12.
    auto doubled{2.0 * readings};
    doubled -= readings;
    std::println("2 * readings - readings == readings: {}", doubled == readings);

    // Any number type works: a matrix of whole numbers, here the number of
    // alarms per station and per day.
    Matrix<int, 2, 3> alarms{0, 2, 1,
                             3, 0, 4};
    std::println("\nalarms (int matrix):\n{:3}", alarms);
    std::println("alarms * 10:\n{:3}", alarms * 10);

    // The identity, and the trace, exist only for square matrices.
    auto identity{Matrix<double, 3, 3>::identity()};
    std::println("\nidentity (3 x 3), trace {}:\n{:.0f}", identity.trace(), identity);

    // The compiler can do the arithmetic. These are checked while compiling,
    // and the results are part of the program.
    constexpr Matrix<int, 2, 2> m{1, 2, 3, 4};
    constexpr auto squared{m * m};
    static_assert(squared[0, 0] == 7 && squared[0, 1] == 10 && squared[1, 0] == 15 && squared[1, 1] == 22);
    constexpr long long fib{fibonacci(30)};
    static_assert(fib == 832'040);
    std::println("\nfibonacci(30), computed by the compiler with matrix products: {}", fib);
    std::println("fibonacci(10) at run time: {}", fibonacci(10));

    // None of the following compile. Each mistake is found by the compiler, at
    // the line where it is made, and not by a test at run time (13.10).
    //
    //   auto a{readings + by_hour};                  // a 3 x 4 matrix plus a 4 x 3 one
    //   auto b{readings * readings};                 // (3 x 4) times (3 x 4): the inner sizes 4 and 3 differ
    //   auto c{Matrix<double, 2, 3>::identity()};    // a 2 x 3 matrix is not square
    //   Matrix<double, 2, 2> d{1, 2, 3};             // three numbers for four cells
    //   Matrix<std::string, 2, 2> e;                 // a string is not a Number
    return 0;
}
