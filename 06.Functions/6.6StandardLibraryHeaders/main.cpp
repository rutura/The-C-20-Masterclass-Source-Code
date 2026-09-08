#include <cmath>       // math functions: sqrt, pow, ceil, floor, fmod
#include <numbers>     // math constants: numbers::pi, numbers::e  (C++20)
#include <random>      // random-number engines and distributions
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector
#include <print>       // std::print / std::println  (C++23)

// The Standard Library groups related functions and types into HEADERS.
// You #include the header for whatever you want to use. A rough map of
// the ones this course reaches for early:
//
//   <iostream>     std::cin, std::cout
//   <print>        std::print, std::println
//   <string>       std::string
//   <string_view>  std::string_view
//   <vector>       std::vector
//   <cmath>        sqrt, pow, abs, ceil, floor, fmod, ...
//   <numbers>      numbers::pi and friends
//   <random>       default_random_engine, uniform_int_distribution, random_device
//   <algorithm>    sort, find, count, min, max, ...
//
// The names live in namespace std, so you qualify them: std::sqrt,
// std::vector, and so on.

int main() {

    std::vector<int> data{9, 3, 7, 1};
    double root{std::sqrt(2.0)};
    std::string label{"headers"};

    std::println("vector size: {}", data.size());
    std::println("sqrt(2)    : {}", root);
    std::println("label      : {}", label);
    std::println("pi         : {}", std::numbers::pi);

    return 0;
}
