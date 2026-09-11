#include "geometry.h"   // include our own header so the compiler checks
                        // these definitions against the declarations

#include <numbers>      // std::numbers::pi (C++20)

// If your compiler predates C++20's <numbers>, drop the include above and
// use a local constant instead:
//
//     namespace { constexpr double pi{3.141592653589793}; }
//
// then write `pi` in place of `std::numbers::pi` below.

// DEFINITIONS - the bodies. Compiled on their own into geometry.o, then
// the linker connects the calls in main.o to these.

double circle_area(double radius) {
    return std::numbers::pi * radius * radius;
}

double circle_circumference(double radius) {
    return 2.0 * std::numbers::pi * radius;
}
