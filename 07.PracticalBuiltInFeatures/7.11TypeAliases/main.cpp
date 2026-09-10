#include <cstdint>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>

// A type alias gives an existing type a second, shorter name. It creates
// NO new type - Celsius below is exactly double, interchangeable with it.
// The point is readability: a long nested type written once, named, then
// used everywhere.

// Modern spelling: `using Name = Type;`. Reads left to right.
using Celsius = double;
using Reading = std::int64_t;

// The old spelling, `typedef Type Name;`, means the same thing but reads
// backwards and cannot be templated. Prefer `using`.
// typedef double Celsius;

// Where aliases really pay off: a nested container type you would
// otherwise retype at every function signature and variable.
using Sample = std::vector<Reading>;
using SamplesByStation = std::unordered_map<std::string, Sample>;

Celsius average(const Sample& s) {
    if (s.empty()) {
        return 0.0;
    }
    Reading total{0};
    for (Reading r : s) {
        total += r;
    }
    return static_cast<Celsius>(total) / s.size();
}

int main() {
    // Celsius is just double - mix them freely, no conversions needed.
    Celsius body_temp{36.8};
    double delta{0.4};
    Celsius fever{body_temp + delta};
    std::println("body {} + {} = {}", body_temp, delta, fever);

    // The alias makes this declaration legible; spell out the full type
    // here and the line is twice as long and half as clear.
    SamplesByStation stations{
        {"roof",     {21, 22, 24, 23, 22}},
        {"basement", {17, 17, 18, 18}},
    };

    for (const auto& [name, sample] : stations) {
        std::println("station {:>9}: {} readings, avg {:.2f}",
                     name, sample.size(), average(sample));
    }

    return 0;
}
