#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <print>
#include <string_view>
#include <vector>

// std::println("{}", some_vector) prints a whole vector in C++23, but only
// GCC 15 or later and current MSVC support it; GCC 14's library does not. This
// small function template (6.13) works everywhere: T is deduced from the
// element type of the vector it is given.
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<22}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

// Modifying algorithms CHANGE values, or copy them somewhere else. They never
// change the SIZE of a container: they work through iterators (14.2).

int main() {

    std::vector<double> celsius{11.5, 18.5, 15.0, -99.0, 24.0, 20.5};
    show("celsius:", celsius);

    // transform: apply a function to every element, writing the results out.
    // The destination must already have room.
    std::println("\n--- transform");
    std::vector<double> fahrenheit(celsius.size());                  // () : N elements, not {} : a list (7.4)
    std::ranges::transform(celsius, fahrenheit.begin(), [](double c) { return c * 9.0 / 5.0 + 32.0; });
    show("fahrenheit:", fahrenheit);

    // With nothing sized yet, write through an INSERTER: it calls push_back for
    // every value it is given. (reserve() is not enough: it creates no elements,
    // so writing through begin() of the empty vector would be undefined behaviour.)
    std::vector<double> converted;
    converted.reserve(celsius.size());
    std::ranges::transform(celsius, std::back_inserter(converted), [](double c) { return c + 273.0; });
    show("kelvin (rounded):", converted);

    // Two inputs at once: one value from each, side by side.
    std::vector<double> offsets{0.5, 0.5, -0.5, 0.0, 1.0, 0.0};
    std::vector<double> corrected;
    std::ranges::transform(celsius, offsets, std::back_inserter(corrected), std::plus<>{});
    show("corrected:", corrected);

    // copy and copy_if.
    std::println("\n--- copy, copy_if");
    std::vector<double> warm;
    std::ranges::copy_if(celsius, std::back_inserter(warm), [](double c) { return c > 17.0; });
    show("warm only:", warm);

    // replace: change values in place.
    std::println("\n--- replace_if, fill, iota, generate");
    std::vector<double> repaired{celsius};
    std::ranges::replace_if(repaired, [](double c) { return c < -50.0; }, 0.0);
    show("broken became 0:", repaired);

    std::vector<int> hours(6);
    std::ranges::iota(hours, 6);                                     // 6, 7, 8 ... (C++23 algorithm)
    show("iota from 6:", hours);

    std::ranges::fill(hours, 0);
    show("fill with 0:", hours);

    int next_hour{0};
    std::ranges::generate(hours, [&] { return next_hour += 4; });    // call the function for each element
    show("generate +4:", hours);

    // Rearranging.
    std::println("\n--- reverse, rotate");
    std::vector<int> day{0, 6, 12, 18};
    std::ranges::reverse(day);
    show("reversed:", day);

    // rotate makes the middle element the new first one: the day now starts at 12.
    std::vector<int> shifted{0, 6, 12, 18};
    std::ranges::rotate(shifted, shifted.begin() + 2);
    show("rotated to 12:", shifted);

    // unique removes CONSECUTIVE duplicates, so sort first. It does not shrink
    // the vector (15.5): it returns the new logical end.
    std::println("\n--- sort, then unique");
    std::vector<int> stations_seen{3, 1, 3, 2, 1, 3};
    std::ranges::sort(stations_seen);
    auto removed{std::ranges::unique(stations_seen)};                // a subrange of the leftover tail
    stations_seen.erase(removed.begin(), removed.end());
    show("distinct:", stations_seen);
    return 0;
}
