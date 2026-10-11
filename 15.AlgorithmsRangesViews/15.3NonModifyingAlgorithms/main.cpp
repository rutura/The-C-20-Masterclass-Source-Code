#include <algorithm>
#include <print>
#include <string>
#include <vector>

// Non-modifying algorithms LOOK at a range and answer a question. Nothing in
// the container changes.

struct Reading {
    std::string station;
    int hour;
    double celsius;
};

int main() {

    // -99.0 is what a broken sensor reports.
    std::vector<Reading> readings{
        {"north", 6, 11.5}, {"north", 12, 18.5}, {"north", 18, 15.0},
        {"south", 6, 14.0}, {"south", 12, 24.0}, {"south", 18, 20.5},
        {"east", 6, 12.5},  {"east", 12, 21.5},  {"east", 18, 17.0},
        {"west", 6, 9.0},   {"west", 12, 16.0},  {"west", 18, -99.0}};

    auto is_broken{[](const Reading& r) { return r.celsius < -50.0; }};
    auto is_hot{[](const Reading& r) { return r.celsius > 20.0; }};

    // "Is there one?", "are they all?", "is there none?" Three yes/no questions.
    std::println("--- any_of, all_of, none_of");
    std::println("any broken?   {}", std::ranges::any_of(readings, is_broken));
    std::println("all hot?      {}", std::ranges::all_of(readings, is_hot));
    std::println("none frozen?  {}", std::ranges::none_of(readings, [](const Reading& r) { return r.celsius < -10.0 && r.celsius > -50.0; }));

    // Counting.
    std::println("\n--- count_if");
    std::println("hot readings: {}", std::ranges::count_if(readings, is_hot));
    std::println("readings at hour 12: {}", std::ranges::count_if(readings, [](const Reading& r) { return r.hour == 12; }));

    // Finding returns an iterator; end() means "none".
    std::println("\n--- find_if, find_if_not, find_last_if");
    auto first_hot{std::ranges::find_if(readings, is_hot)};
    if (first_hot != readings.end()) {
        std::println("first hot one: {} at {}h, {}", first_hot->station, first_hot->hour, first_hot->celsius);
    }
    auto first_broken{std::ranges::find_if(readings, is_broken)};
    if (first_broken != readings.end()) {
        std::println("broken sensor: {} at {}h", first_broken->station, first_broken->hour);
    }
    auto not_north{std::ranges::find_if_not(readings, [](const Reading& r) { return r.station == "north"; })};
    std::println("first reading that is not north: {}", not_north->station);
    auto last_hot{std::ranges::find_last_if(readings, is_hot)};            // C++23: returns a subrange
    std::println("last hot one: {} at {}h", last_hot.front().station, last_hot.front().hour);

    // Smallest and largest, with the rule that says how to compare.
    std::println("\n--- min_element, max_element");
    auto by_temperature{[](const Reading& a, const Reading& b) { return a.celsius < b.celsius; }};
    // The readings that are not broken. (A loop for now: 15.4 does this in one line, with copy_if.)
    std::vector<Reading> good;
    for (const auto& reading : readings) {
        if (!is_broken(reading)) {
            good.push_back(reading);
        }
    }
    auto coldest{std::ranges::min_element(good, by_temperature)};
    auto warmest{std::ranges::max_element(good, by_temperature)};
    std::println("coldest: {} {}h {}", coldest->station, coldest->hour, coldest->celsius);
    std::println("warmest: {} {}h {}", warmest->station, warmest->hour, warmest->celsius);

    // Comparing two sequences.
    std::println("\n--- equal, mismatch");
    std::vector<int> expected_hours{6, 12, 18, 6, 12, 18, 6, 12, 18, 6, 12, 18};
    std::vector<int> actual_hours;
    for (const auto& r : readings) {
        actual_hours.push_back(r.hour);
    }
    std::println("hours as expected: {}", std::ranges::equal(expected_hours, actual_hours));
    actual_hours[7] = 13;
    auto [first_expected, first_actual]{std::ranges::mismatch(expected_hours, actual_hours)};
    std::println("first difference at index {}: expected {}, got {}",
                 first_expected - expected_hours.begin(), *first_expected, *first_actual);

    // Looking for a pattern of values.
    std::println("\n--- search, adjacent_find, contains");
    std::vector<int> hours{6, 12, 18, 6, 12, 12, 18};
    std::vector<int> pattern{12, 18};
    auto where{std::ranges::search(hours, pattern)};
    std::println("pattern 12,18 first found at index {}", where.begin() - hours.begin());
    auto twice{std::ranges::adjacent_find(hours)};                        // two equal neighbours
    std::println("first repeated neighbour at index {}", twice - hours.begin());
    std::println("contains 18: {}   contains 24: {}", std::ranges::contains(hours, 18), std::ranges::contains(hours, 24));

    // for_each: do something to every element. Often a range-based for loop is clearer.
    std::println("\n--- for_each");
    double total{0.0};
    std::ranges::for_each(good, [&](const Reading& r) { total += r.celsius; });
    std::println("average of the {} good readings: {:.2f}", good.size(), total / static_cast<double>(good.size()));
    return 0;
}
