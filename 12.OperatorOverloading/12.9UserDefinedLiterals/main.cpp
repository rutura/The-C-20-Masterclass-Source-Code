#include <chrono>
#include <print>
#include <string>

// A length stored in metres, whatever unit it was written in.
struct Length {
    double meters;
};

constexpr Length operator+(Length a, Length b) {
    return Length{a.meters + b.meters};
}

// A USER-DEFINED LITERAL: a suffix that turns a number into a value of your
// type. The operator is called operator"" followed by the suffix. Rules:
//   - your own suffixes MUST start with an underscore (suffixes without one are
//     reserved for the standard library: s, ms, h, ...)
//   - the parameter is long double (for 1.5_km) or unsigned long long (for 5_km)
// constexpr, so that a literal can also be used in constant expressions.
constexpr Length operator""_m(long double value) {
    return Length{static_cast<double>(value)};
}

constexpr Length operator""_km(long double value) {
    return Length{static_cast<double>(value) * 1000.0};
}

constexpr Length operator""_cm(long double value) {
    return Length{static_cast<double>(value) / 100.0};
}

// A second overload for whole-number literals, so that 5_km works as well as 5.0_km.
constexpr Length operator""_km(unsigned long long value) {
    return Length{static_cast<double>(value) * 1000.0};
}

// A literal for text: it receives a pointer to the characters and their count.
std::string operator""_tag(const char* text, std::size_t length) {
    return "[" + std::string{text, length} + "]";
}

int main() {

    // Without literals: units hide in comments and variable names.
    Length without{1500.0};                        // metres? kilometres? who knows
    std::println("a bare 1500.0 says nothing about its unit: {}", without.meters);

    // With them: the unit is in the code, and the value is stored in one unit.
    Length road{1.5_km};
    Length track{250.0_m};
    Length crack{3.5_cm};

    std::println("1.5_km   = {} m", road.meters);
    std::println("250.0_m  = {} m", track.meters);
    std::println("3.5_cm   = {} m", crack.meters);
    std::println("5_km     = {} m  (the whole-number overload)", (5_km).meters);

    Length total{road + track + crack};
    std::println("\nroad + track + crack = {} m", total.meters);

    // constexpr: computed while compiling, and usable where a constant is required.
    constexpr Length marathon{42.195_km};
    static_assert(marathon.meters > 42000.0);
    std::println("a marathon: {} m", marathon.meters);

    std::println("\nthe text literal: {}", "north"_tag);

    // You have used literals like these since chapter 7. They are the same
    // mechanism, defined by the standard library, and they live in a namespace
    // that you bring in with a using directive:
    using namespace std::chrono_literals;
    auto timeout{250ms};
    auto period{2min};
    std::println("\n250ms is {} and 2min is {}", timeout, period);

    // A good use of user-defined literals: units, where a wrong guess is
    // expensive. A poor use: anything where the suffix is not obvious to a reader.
    return 0;
}
