#include <algorithm>
#include <chrono>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "rapidcsv.h"

/*
    Chapter 7 assignment - Practical built-in features (SOLUTION)
*/

std::vector<int> grow_readings(const std::vector<int>& source, int extra);
void warmest_and_coolest(const std::vector<int>& data, int& coolest, int& warmest);
std::string clean_label(std::string label);
std::string format_receipt(const std::string& item, int quantity, double price);
long days_until(std::chrono::year_month_day target);

int main() {

    const std::vector<int> temperatures{68, 72, 59, 81, 90, 55, 77, 64};

    // --- Exercise 1 ---------------------------------------------------------
    std::println("--- Exercise 1: grow_readings ---");
    std::vector<int> grown{grow_readings(temperatures, 100)};
    std::print("size: {}\n", grown.size());
    for (const int& reading : grown) {
        std::print("{} ", reading);
    }
    std::println("");

    // --- Exercise 2 ----------------------------------------------------------
    std::println("\n--- Exercise 2: warmest_and_coolest ---");
    int coolest{};
    int warmest{};
    warmest_and_coolest(temperatures, coolest, warmest);
    std::println("coolest = {}, warmest = {}", coolest, warmest);

    std::print("temperatures (unchanged): ");
    for (const int& reading : temperatures) {
        std::print("{} ", reading);
    }
    std::println("");

    // --- Exercise 3 ------------------------------------------------------------
    std::println("\n--- Exercise 3: average_of_hot_days ---");
    auto hotDays{
        temperatures | std::views::filter([](int t) { return t > 70; })};

    const auto hotDayCount{std::ranges::distance(hotDays)};
    const double hotDayAverage{
        std::accumulate(hotDays.begin(), hotDays.end(), 0.0) / hotDayCount};

    std::println("hot days: {}", hotDayCount);
    std::println("average: {:.2f}", hotDayAverage);

    // --- Exercise 4 ---------------------------------------------------------
    std::println("\n--- Exercise 4: clean_label ---");
    std::println("{}", clean_label("sensor reading #3 (raw)"));

    // --- Exercise 5 -----------------------------------------------------------
    std::println("\n--- Exercise 5: extract_reading ---");
    std::istringstream line{"sensor-7 42.5 ok"};
    std::string name;
    double reading{};
    std::string status;
    line >> name >> reading >> status;

    std::println("name: {}", name);
    std::println("reading: {}", reading);
    std::println("status: {}", status);

    // --- Exercise 6 -------------------------------------------------------------
    std::println("\n--- Exercise 6: flagged_accounts ---");
    rapidcsv::Document accounts{"accounts.csv"};
    std::vector<std::string> names{accounts.GetColumn<std::string>("name")};
    std::vector<double> balances{accounts.GetColumn<double>("balance")};

    std::regex shortName{"[A-Z][a-z]{0,3}"};

    for (std::size_t i{0}; i < names.size(); ++i) {
        if (std::regex_match(names.at(i), shortName)) {
            std::println("{}: {}", names.at(i), balances.at(i));
        }
    }

    // --- Exercise 7 ---------------------------------------------------------
    std::println("\n--- Exercise 7: format_receipt ---");
    std::println("{}", format_receipt("coffee", 2, 4.5));
    std::println("{}", format_receipt("bagel", 1, 3.25));
    std::println("{}", format_receipt("tea", 10, 2.0));

    // --- Exercise 8 -----------------------------------------------------------
    std::println("\n--- Exercise 8: days_until ---");
    const std::chrono::year_month_day target{std::chrono::year{2026} / 12 / 25};
    std::println("{} days until {}", days_until(target), target);

    return 0;
}

// Starts empty, then builds itself up one push_back at a time.
std::vector<int> grow_readings(const std::vector<int>& source, int extra) {
    std::vector<int> readings{};

    for (const int& value : source) {
        readings.push_back(value);
    }
    readings.push_back(extra);

    return readings;
}

// Sorts a local copy so the caller's vector is never touched.
void warmest_and_coolest(const std::vector<int>& data, int& coolest, int& warmest) {
    std::vector<int> sorted{data};
    std::ranges::sort(sorted);

    coolest = sorted.front();
    warmest = sorted.back();
}

// Drops a trailing "#..." comment, then swaps spaces for underscores.
std::string clean_label(std::string label) {
    std::size_t hashPos{label.find('#')};
    if (hashPos != std::string::npos) {
        label.erase(hashPos);
    }

    std::size_t spacePos{label.find(' ')};
    while (spacePos != std::string::npos) {
        label.replace(spacePos, 1, "_");
        spacePos = label.find(' ', spacePos + 1);
    }

    return label;
}

// Left-aligns the name, right-aligns quantity and price into fixed-width
// fields using the {:...} spec grammar - no manual padding.
std::string format_receipt(const std::string& item, int quantity, double price) {
    return std::format("{:<12}{:>4}{:>8.2f}", item, quantity, price);
}

// Converts both dates to sys_days (a count of days since the epoch) so
// they can be subtracted directly; year_month_day itself has no -.
long days_until(std::chrono::year_month_day target) {
    const auto today{std::chrono::floor<std::chrono::days>(
        std::chrono::system_clock::now())};
    const auto targetDays{static_cast<std::chrono::sys_days>(target)};

    return (targetDays - today).count();
}
