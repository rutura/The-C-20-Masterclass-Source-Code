#include <cmath>     // std::sqrt, std::pow, std::ceil, std::floor, std::fmod ...
#include <numbers>   // std::numbers::pi (C++20)
#include <print>

// The <cmath> header is a large set of ready-made math functions. You
// call them exactly like functions you wrote: name, arguments, use the
// returned value.

int main() {

    double x{2.0};
    double y{9.0};

    std::println("sqrt(9.0)        = {}", std::sqrt(y));
    std::println("pow(2.0, 10.0)   = {}", std::pow(x, 10.0));
    std::println("ceil(2.3)        = {}", std::ceil(2.3));
    std::println("floor(2.8)       = {}", std::floor(2.8));
    std::println("fmod(10.0, 3.0)  = {}", std::fmod(10.0, 3.0));   // 1.0 (float remainder)
    std::println("abs(-4.5)        = {}", std::abs(-4.5));

    // C++20 gives named math constants in <numbers>.
    double radius{3.0};
    double area{std::numbers::pi * radius * radius};
    std::println("circle area (r=3) = {}", area);

    // These are just functions. Nothing special about the call syntax -
    // the work of writing them was done for you.

    return 0;
}
