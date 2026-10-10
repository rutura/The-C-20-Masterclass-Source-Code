#include <algorithm>
#include <compare>
#include <cstddef>
#include <format>
#include <print>
#include <string>
#include <utility>
#include <vector>

/*
    Chapter 12 assignment - Operator overloading

    Eight small types for the weather station, one operator idea each. Write
    the classes ABOVE main(), and the lines that use them in main() under the
    exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
        (a using-directive for a literals namespace is fine, as in 7.10).
      - An operator must do what its symbol suggests.
      - Mark every member function that does not change the object const.
*/

// Provided for exercise 2.
struct Wind {
    double speed;        // km/h
    double heading;      // degrees
};

// Write your classes here, above main().


int main() {

    /*
        Exercise 1 - arithmetic operators

        Write class Vec2 (two private doubles, a constructor Vec2(x, y), and
        getters x() and y()) with these operators, following 12.3: the compound
        ones as members, the binary ones built from them as hidden friends:

            Vec2& operator+=(const Vec2&)
            friend Vec2 operator+(Vec2, const Vec2&)
            Vec2 operator-() const                       // unary minus
            friend Vec2 operator*(Vec2, double)
            friend Vec2 operator*(double, Vec2)          // both orders

        With a{1, 2} and b{3, 4}, print each result as "(x, y)" using the
        getters.

        Sample output:
            a + b = (4, 6)
            -a = (-1, -2)
            2 * a = (2, 4)
            a * 3 = (3, 6)
            after a += b: (4, 6)
    */
    std::println("--- Exercise 1: arithmetic operators ---");
    // TODO


    /*
        Exercise 2 - std::formatter

        Teach std::println about the provided struct Wind. Specialize
        std::formatter<Wind> (as in 12.4, reusing a std::formatter<double> for
        the numbers) so that a Wind prints as "<speed> km/h at <heading> deg".
        A format spec given after the colon must apply to both numbers.

        Print Wind{12.5, 270.0} with {} and with {:.1f}.

        Sample output:
            12.5 km/h at 270 deg
            12.5 km/h at 270.0 deg
    */
    std::println("--- Exercise 2: std::formatter ---");
    // TODO


    /*
        Exercise 3 - comparison

        Write struct Version { int major; int minor; int patch; } with a
        defaulted <=> (12.5). Put these in a std::vector<Version>, in this
        order: {1, 2, 0}, {1, 10, 0}, {0, 9, 2}, {1, 0, 0}. Sort it with
        std::ranges::sort, and print the versions as "major.minor.patch" on one
        line. Then print whether Version{1, 10, 0} > Version{1, 2, 0}.

        Sample output:
            0.9.2 1.0.0 1.2.0 1.10.0
            1.10.0 > 1.2.0: true
    */
    std::println("--- Exercise 3: comparison ---");
    // TODO


    /*
        Exercise 4 - the subscript operator

        Write class Grid, a table of doubles with rows and columns, stored in
        one std::vector<double>, row after row. Give it a constructor
        Grid(rows, columns) that fills everything with 0.0, and the C++23
        multi-argument subscript operator in two versions (12.6): a writable one
        and a const one, both taking (row, column).

        Make a 2 x 3 grid, set grid[0, 0] to 1.0 and grid[1, 2] to 5.0, then
        print grid[1, 2] and the total of all six cells (loop with two for
        loops over row and column; you need rows() and columns() getters).

        Sample output:
            grid[1, 2] = 5, total = 6
    */
    std::println("--- Exercise 4: the subscript operator ---");
    // TODO


    /*
        Exercise 5 - the call operator

        Write a function object Clamp: its constructor takes low and high, and
        its operator()(double) const returns the value forced into that range.
        Apply Clamp{0.0, 30.0} to the vector {-5.0, 12.0, 40.0, 18.0, 100.0}
        with std::ranges::transform into a second vector, and print the result.

        Sample output:
            0 12 30 18 30
    */
    std::println("--- Exercise 5: the call operator ---");
    // TODO


    /*
        Exercise 6 - conversions

        Write class Percent that holds a double. Its constructor takes the value
        and is explicit. Give it an `explicit operator double() const` and an
        `explicit operator bool() const` that is true when the value is above
        zero. Make Percent{75.0} and Percent{0.0}. For each, print the number
        (static_cast<double>) and whether it is "truthy", using it directly in
        an if.

        Sample output:
            75 percent, truthy: yes
            0 percent, truthy: no
    */
    std::println("--- Exercise 6: conversions ---");
    // TODO


    /*
        Exercise 7 - user-defined literals

        Write struct Mass { double kilograms; } with an operator+ (a free
        function), and two literal operators, as in 12.9:

            operator""_kg(long double)      // 2.5_kg is 2.5 kilograms
            operator""_g(long double)       // 500.0_g is 0.5 kilograms

        Compute 2.5_kg + 500.0_g and print the total in kilograms.

        Sample output:
            3 kg
    */
    std::println("--- Exercise 7: user-defined literals ---");
    // TODO


    /*
        Exercise 8 - a pipe operator

        Write struct Series { std::vector<double> values; }, two function
        objects Scale{factor} and Offset{amount} whose operator() takes a Series
        and returns a new one (every value multiplied by factor, or increased by
        amount), and a template operator| (12.10):

            template <typename Step> Series operator|(Series series, Step step);

        Run  Series{{1.0, 2.0, 3.0}} | Scale{2.0} | Offset{1.0}  and print the
        values.

        Sample output:
            3 5 7
    */
    std::println("--- Exercise 8: a pipe operator ---");
    // TODO

    return 0;
}
