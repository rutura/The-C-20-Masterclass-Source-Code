#include <iostream>
#include <cmath>
#include <numeric>
#include <numbers>
#include <algorithm>
#include <vector>
#include <string>
#include <bit>
#include <print>

int main(){
    // --- Math: <cmath> and <numbers> ---
    std::println("sqrt(9.0)  = {}", std::sqrt(9.0));
    std::println("sqrt(81)  = {}", std::sqrt(81));
    std::println("pow(2.0, 10.0)   = {}", std::pow(2.0, 10.0));
    std::println("hypot(3.0, 4.0)  = {}", std::hypot(3.0, 4.0));
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

    // Setup a collection of integers
    std::vector<int> v{ 5, 2, 8, 1, 9, 3 };

    // Sort the collection
    std::ranges::sort(v);

    for (int i{ 0 }; i < v.size(); ++i) {
        std::print("{} ", v[i]);
    }
    std::println("");


    // --- Text queries: <string> ---
    std::string message{ "hello world" };
    std::println("starts_with(\"hello\") = {}", message.starts_with("hello"));
    std::println("ends_with(\"world\")   = {}", message.ends_with("world"));
    std::println("contains(\"lo wo\")    = {}", message.contains("lo wo"));  // C++23

    // --- Bit inspection: <bit> (C++20) ---
    unsigned int flags{ 0b1011'0100 };
    std::println("popcount(0b10110100)      = {}", std::popcount(flags));   // set bits
    std::println("bit_width(0b10110100)     = {}", std::bit_width(flags));  // bits needed
    std::println("has_single_bit(64u)       = {}", std::has_single_bit(64u)); // power of two?
}