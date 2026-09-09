#include <algorithm>   // std::min, std::max, std::clamp, std::ranges::sort
#include <bit>         // std::popcount, std::bit_width, std::has_single_bit  (C++20)
#include <cmath>       // std::sqrt, std::pow, std::hypot
#include <numbers>     // std::numbers::pi, std::numbers::e                   (C++20)
#include <numeric>     // std::gcd, std::lcm                                 (C++17)
#include <print>
#include <string>
#include <vector>

// You don't have to write everything. The C++ Standard Library ships
// thousands of ready-made functions across many headers. You call them
// exactly like functions you wrote - name, arguments, use the result.
// The library also keeps growing: each new standard adds more. Here is a
// small tour, with the standard that introduced the newer ones noted.

int main() {

    // --- Math: <cmath> and <numbers> ---
    std::println("sqrt(9.0)        = {}", std::sqrt(9.0));
    std::println("pow(2.0, 10.0)   = {}", std::pow(2.0, 10.0));
    std::println("hypot(3.0, 4.0)  = {}", std::hypot(3.0, 4.0));   // sqrt(a*a+b*b), no overflow
    std::println("lerp(0, 100, .25) = {}", std::lerp(0.0, 100.0, 0.25));  // C++20: blend a->b
    std::println("midpoint(10, 20)  = {}", std::midpoint(10, 20)); // C++20: safe average
    std::println("pi                = {}", std::numbers::pi);      // C++20

    // --- Numeric helpers: <numeric> ---
    std::println("gcd(24, 36)      = {}", std::gcd(24, 36));       // C++17
    std::println("lcm(4, 6)        = {}", std::lcm(4, 6));         // C++17

    // --- Picking / bounding values: <algorithm> ---
    std::println("min(7, 3)        = {}", std::min(7, 3));
    std::println("max(7, 3)        = {}", std::max(7, 3));
    std::println("clamp(150, 0, 100) = {}", std::clamp(150, 0, 100));  // C++17: keep in range

    std::vector<int> v{5, 2, 8, 1, 9, 3};
    std::ranges::sort(v);                                          // C++20: sort a whole range
    std::print("sorted: ");
    for (int n : v) { std::print("{} ", n); }
    std::println("");

    // --- Text queries: <string> ---
    std::string message{"hello world"};
    std::println("starts_with(\"hello\") = {}", message.starts_with("hello"));
    std::println("ends_with(\"world\")   = {}", message.ends_with("world"));
    std::println("contains(\"lo wo\")    = {}", message.contains("lo wo"));  // C++23

    // --- Bit inspection: <bit> (C++20) ---
    unsigned int flags{0b1011'0100};
    std::println("popcount(0b10110100)      = {}", std::popcount(flags));   // set bits
    std::println("bit_width(0b10110100)     = {}", std::bit_width(flags));  // bits needed
    std::println("has_single_bit(64u)       = {}", std::has_single_bit(64u)); // power of two?

    return 0;
}
