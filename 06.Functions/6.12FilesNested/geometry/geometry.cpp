#include "geometry.h"

#include <numbers>      // std::numbers::pi (C++20)

// Pre-C++20 compiler? Drop the include and use a local constant instead:
//     namespace { constexpr double pi{3.141592653589793}; }
// then write `pi` for `std::numbers::pi` below.

double circle_area(double radius) {
    return std::numbers::pi * radius * radius;
}

double circle_circumference(double radius) {
    return 2.0 * std::numbers::pi * radius;
}
