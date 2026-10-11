#include <algorithm>
#include <format>
#include <functional>
#include <iterator>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

struct Reading {
    std::string station;
    int hour;
    double celsius;
};

// -99.0 is what a broken sensor reports.
const std::vector<Reading> table{
    {"north", 6, 11.5}, {"north", 12, 18.5}, {"north", 18, 15.0},
    {"south", 6, 14.0}, {"south", 12, 24.0}, {"south", 18, 20.5},
    {"east", 6, 12.5},  {"east", 12, 21.5},  {"east", 18, 17.0},
    {"west", 6, 9.0},   {"west", 12, 16.0},  {"west", 18, -99.0}};

bool is_broken(const Reading& r) {
    return r.celsius < -50.0;
}

template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<16}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

int main() {

    std::println("--- Exercise 1: asking questions ---");
    std::println("any broken: {}", std::ranges::any_of(table, is_broken));
    std::println("hot readings (above 20): {}", std::ranges::count_if(table, [](const Reading& r) { return r.celsius > 20.0; }));
    auto broken{std::ranges::find_if(table, is_broken)};
    std::println("first broken: {} at {}h", broken->station, broken->hour);
    std::vector<Reading> valid;
    std::ranges::copy_if(table, std::back_inserter(valid), [](const Reading& r) { return !is_broken(r); });
    auto coldest{std::ranges::min_element(valid, {}, &Reading::celsius)};
    std::println("coldest valid: {} at {}h ({})", coldest->station, coldest->hour, coldest->celsius);

    std::println("\n--- Exercise 2: copy and transform ---");
    std::vector<Reading> south;
    std::ranges::copy_if(valid, std::back_inserter(south), [](const Reading& r) { return r.station == "south"; });
    std::vector<double> south_fahrenheit;
    std::ranges::transform(south, std::back_inserter(south_fahrenheit),
                           [](const Reading& r) { return r.celsius * 9.0 / 5.0 + 32.0; });
    show("south in F:", south_fahrenheit);

    std::println("\n--- Exercise 3: erase_if and unique ---");
    std::vector<Reading> cleaned{table};
    auto removed{std::erase_if(cleaned, is_broken)};
    std::println("removed {}, {} left", removed, cleaned.size());
    std::vector<int> hours;
    std::ranges::transform(cleaned, std::back_inserter(hours), &Reading::hour);
    std::ranges::sort(hours);
    auto tail{std::ranges::unique(hours)};
    hours.erase(tail.begin(), tail.end());
    show("distinct hours:", hours);

    std::println("\n--- Exercise 4: sort with projections ---");
    std::vector<Reading> ordered{cleaned};
    std::ranges::stable_sort(ordered, std::ranges::greater{}, &Reading::celsius);
    std::ranges::stable_sort(ordered, {}, &Reading::station);
    for (const auto& r : ordered | std::views::take(6)) {
        std::println("{:<6} {:>2}h {:5.1f}", r.station, r.hour, r.celsius);
    }

    std::println("\n--- Exercise 5: binary search ---");
    std::vector<double> temperatures{cleaned | std::views::transform(&Reading::celsius) | std::ranges::to<std::vector>()};
    std::ranges::sort(temperatures);
    auto first{std::ranges::lower_bound(temperatures, 15.0)};
    auto last{std::ranges::lower_bound(temperatures, 25.0)};
    std::println("readings from 15 up to (not including) 25: {}", last - first);

    std::println("\n--- Exercise 6: numeric algorithms ---");
    std::vector<int> rain{0, 2, 5, 0, 1, 7, 3, 0};
    std::vector<int> running(rain.size());
    std::inclusive_scan(rain.begin(), rain.end(), running.begin());
    show("running total:", running);
    auto wettest{std::ranges::max_element(rain)};
    std::println("wettest hour: {}h ({} mm)", 6 + (wettest - rain.begin()), *wettest);
    std::println("average: {:.2f} mm", static_cast<double>(std::reduce(rain.begin(), rain.end(), 0)) / static_cast<double>(rain.size()));

    std::println("\n--- Exercise 7: a pipeline of views ---");
    auto summary{cleaned
        | std::views::filter([](const Reading& r) { return r.hour == 12; })
        | std::views::transform([](const Reading& r) { return std::format("{}:{}", r.station, r.celsius); })
        | std::views::take(3)
        | std::views::join_with(std::string_view{", "})
        | std::ranges::to<std::string>()};
    std::println("{}", summary);

    std::println("\n--- Exercise 8: average per station ---");
    auto stations{cleaned | std::views::transform(&Reading::station) | std::ranges::to<std::set>()};
    for (const auto& station : stations) {
        auto temps{cleaned
            | std::views::filter([&](const Reading& r) { return r.station == station; })
            | std::views::transform(&Reading::celsius)
            | std::ranges::to<std::vector>()};
        double average{std::ranges::fold_left(temps, 0.0, std::plus<>{}) / static_cast<double>(temps.size())};
        std::println("{}: {:.1f}", station, average);
    }
    return 0;
}
