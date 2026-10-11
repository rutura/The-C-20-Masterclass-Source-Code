#include <algorithm>
#include <list>
#include <map>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Prints a label and the elements of a vector (as in 15.4).
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<26}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

// "Remove the broken readings" sounds like one step. It is two, because an
// algorithm only has iterators: it cannot shrink a container.

int main() {

    auto is_broken{[](double c) { return c < -50.0; }};

    std::println("--- remove_if does NOT erase");
    std::vector<double> celsius{11.5, -99.0, 15.0, -99.0, 24.0, 20.5};
    show("before:", celsius);

    // remove_if moves the elements to KEEP to the front, in order, and returns
    // an iterator to where the kept ones end. The vector is exactly as long as
    // before. What lies from that point on is "valid but unspecified".
    auto garbage{std::ranges::remove_if(celsius, is_broken)};        // a subrange: the leftover tail
    std::println("size after remove_if: {} (unchanged)", celsius.size());
    std::println("kept: {} elements, tail: {} elements", garbage.begin() - celsius.begin(), garbage.size());

    // The second step: tell the CONTAINER to drop the tail.
    celsius.erase(garbage.begin(), garbage.end());
    show("after erase:", celsius);
    std::println("size now: {}", celsius.size());

    // Those two lines together are the "erase-remove idiom". Written as one,
    // for a vector:
    std::vector<double> again{11.5, -99.0, 15.0, -99.0, 24.0, 20.5};
    again.erase(std::ranges::remove_if(again, is_broken).begin(), again.end());
    show("one line, same result:", again);

    // C++20 turned the idiom into a function that does both steps.
    std::println("\n--- std::erase_if and std::erase");
    std::vector<double> readings{11.5, -99.0, 15.0, -99.0, 24.0, 20.5};
    auto count{std::erase_if(readings, is_broken)};                  // returns how many were removed
    std::println("erase_if removed {}", count);
    show("readings:", readings);

    std::vector<int> hours{6, 12, 6, 18, 6};
    std::erase(hours, 6);                                            // by value
    show("hours without 6:", hours);

    // 14.4 solved this with a loop and the iterator that erase() returns.
    // erase_if is that loop, written once, correctly, for every container.

    // It works on every standard container, each in the best way it can.
    std::println("\n--- the same function on other containers");
    std::list<std::string> jobs{"upload", "test", "calibrate", "test", "report"};
    std::erase(jobs, "test");
    std::print("list without test:         ");
    for (const auto& job : jobs) {
        std::print(" {}", job);
    }
    std::println();

    // For a map, each element is a pair of (const key, value) (14.6), and that
    // is what the predicate receives.
    std::map<std::string, double> latest{{"north", 18.5}, {"south", -99.0}, {"east", 21.5}, {"west", -99.0}};
    std::erase_if(latest, [](const std::pair<const std::string, double>& entry) { return entry.second < -50.0; });
    std::print("map without broken:        ");
    for (const auto& [station, celsius_value] : latest) {
        std::print(" {}={}", station, celsius_value);
    }
    std::println();

    // Why can a MAP not use remove_if? remove_if moves elements forward by
    // assigning over them, and the key of a map element is const (14.6): the
    // sorted order must not change under the map's feet. The map's erase_if
    // erases the matching nodes one by one instead.
    return 0;
}
