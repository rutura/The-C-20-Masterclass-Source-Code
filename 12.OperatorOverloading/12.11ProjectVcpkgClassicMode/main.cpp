#include <vector>

#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

// PROJECT, part A: use a library that is NOT part of your project and NOT part
// of the C++ standard library, installed with vcpkg in "classic mode".
//
// The library is {fmt}. It is the library std::format and std::print were
// standardized from (chapter 3 and 7.8), so everything below looks familiar,
// with a few extras the standard version does not have. Nothing in this folder
// contains fmt's code: vcpkg downloaded it, built it and installed it somewhere
// else, and CMake finds it there.

int main() {

    const std::vector<double> readings{68.0, 71.5, 69.0, 72.0, 70.5};

    // The same format-string language as std::println.
    fmt::print("{:<10} | {:>8} | {:^8}\n", "sensor", "reading", "status");
    fmt::print("{:<10} | {:>8.1f} | {:^8}\n", "north", readings[0], "ok");
    fmt::print("{:<10} | {:>8.1f} | {:^8}\n", "east", readings[1], "ok");

    // Extras: a vector prints as a list, and join glues the elements together.
    fmt::print("\nreadings: {}\n", readings);
    fmt::print("joined:   {}\n", fmt::join(readings, " / "));

    // Colour, with a style object in front of the format string.
    fmt::print(fg(fmt::color::orange) | fmt::emphasis::bold, "warm day: {} F\n", readings[3]);

    // fmt::format returns a std::string, like std::format.
    std::string line{fmt::format("{} readings, first {}", readings.size(), readings.front())};
    fmt::print("{}\n", line);

    return 0;
}
