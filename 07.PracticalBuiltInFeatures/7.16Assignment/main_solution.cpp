#include <algorithm>
#include <chrono>
#include <format>
#include <numeric>
#include <print>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 7 assignment - Practical built-in features (SOLUTION)
*/

std::vector<int> top_n(const std::vector<int>& data, std::size_t n);
bool is_registered(const std::vector<std::string>& sorted_ids, const std::string& id);
std::string_view sensor_number(std::string_view name);
std::string format_row(std::string_view number, double reading, const std::string& status);
long long days_until(std::chrono::year_month_day target);
bool is_valid_sensor_id(const std::string& id);

int main() {

    const std::vector<int> temperatures{68, 72, 59, 81, 90, 55, 77, 64};
    const std::vector<std::string> sensor_ids{
        "sensor-12", "sensor-3", "sensor-27", "sensor-8", "sensor-1"};
    const std::vector<std::string> raw_lines{
        "sensor-7 42.5 ok #calibrated", "sensor-12 8.25 low", "sensor-3 100 ok #spare"};
    const std::string log_line{
        "14:06:09 ERROR sensor-7 temp=91, "
        "14:07:12 WARN sensor-12 temp=88, "
        "14:09:45 INFO sensor-3 temp=71"};

    // --- Exercise 1 ---------------------------------------------------------
    std::println("--- Exercise 1: sorting and searching ---");

    // Part A: sort a copy once, then search it as often as we like.
    std::vector<std::string> sorted_ids{sensor_ids};
    std::ranges::sort(sorted_ids);

    std::print("sorted:");
    for (const std::string& id : sorted_ids) {
        std::print(" {}", id);
    }
    std::println("");

    std::println("sensor-27 registered: {}", is_registered(sorted_ids, "sensor-27"));
    std::println("sensor-99 registered: {}", is_registered(sorted_ids, "sensor-99"));

    // Part B: its own copy. Sorting by length would break the alphabetical
    // order that binary_search relies on in sorted_ids.
    std::vector<std::string> ids_by_length{sensor_ids};
    std::ranges::sort(ids_by_length, [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) {
            return a.size() > b.size();
        }
        return a < b;
    });

    std::print("by length:");
    for (const std::string& id : ids_by_length) {
        std::print(" {}", id);
    }
    std::println("");

    // Part C
    std::print("top 3:");
    for (int temperature : top_n(temperatures, 3)) {
        std::print(" {}", temperature);
    }
    std::println("");

    // --- Exercise 2 ---------------------------------------------------------
    std::println("\n--- Exercise 2: functional style ---");

    // Part A: nothing runs yet, this is only a description of the pipeline.
    auto hot_days_celsius{
        temperatures
        | std::views::filter([](int f) { return f > 70; })
        | std::views::transform([](int f) { return (f - 32) * 5.0 / 9.0; })};

    // Counting is a fold too: ignore the element, add one.
    const int hot_day_count{std::accumulate(
        hot_days_celsius.begin(), hot_days_celsius.end(), 0,
        [](int count, double) { return count + 1; })};

    // 0.0, not 0: an int starting value would truncate every partial sum.
    const double celsius_total{
        std::accumulate(hot_days_celsius.begin(), hot_days_celsius.end(), 0.0)};

    std::println("hot days: {}", hot_day_count);
    std::println("average: {:.2f}", celsius_total / hot_day_count);

    // Part B: start from the first element, keep whichever is larger.
    const int hottest_reading{std::accumulate(
        temperatures.begin(), temperatures.end(), temperatures.front(),
        [](int best, int current) { return current > best ? current : best; })};
    std::println("hottest: {}", hottest_reading);

    // --- Exercise 3 ---------------------------------------------------------
    std::println("\n--- Exercise 3: strings and formatting ---");
    std::println("{:>3} | {:^6} | {:>8}", "id", "status", "reading");

    for (const std::string& raw : raw_lines) {
        std::string cleaned{raw};
        if (std::size_t hash_pos{cleaned.find('#')}; hash_pos != std::string::npos) {
            cleaned.erase(hash_pos);
        }

        std::istringstream fields{cleaned};
        std::string name{};
        double reading{};
        std::string status{};
        fields >> name >> reading >> status;

        // name lives until the end of this iteration, so the view is safe.
        std::println("{}", format_row(sensor_number(name), reading, status));
    }

    // --- Exercise 4 ---------------------------------------------------------
    std::println("\n--- Exercise 4: dates and durations ---");
    const std::chrono::year_month_day target{std::chrono::year{2030} / 1 / 1};
    std::println("{} days until {:%Y-%m-%d}", days_until(target), target);

    // Different units mix freely; chrono picks the common one (seconds).
    const auto on_duty{std::chrono::hours{4} + std::chrono::minutes{90} +
                       std::chrono::seconds{45}};
    std::println("total on duty: {}", on_duty);

    const std::chrono::hh_mm_ss split{on_duty};
    std::println("{}h {}m {}s", split.hours().count(), split.minutes().count(),
                 split.seconds().count());
    std::println("{} whole minutes",
                 std::chrono::duration_cast<std::chrono::minutes>(on_duty).count());

    // --- Exercise 5 ---------------------------------------------------------
    std::println("\n--- Exercise 5: regex ---");

    // Part A
    const std::vector<std::string> candidates{
        "sensor-7", "sensor-1234", "Sensor-7", "sensor-7 "};
    for (const std::string& candidate : candidates) {
        std::println("[{}] -> {}", candidate, is_valid_sensor_id(candidate));
    }

    // Part B: a named regex on purpose, sregex_iterator keeps a pointer to it.
    const std::regex reading_pattern{R"((sensor-\d+) temp=(\d+))"};
    const std::sregex_iterator end{};
    int hottest{0};
    for (auto it = std::sregex_iterator{log_line.cbegin(), log_line.cend(), reading_pattern};
         it != end; ++it) {
        const int temperature{std::stoi((*it)[2].str())};
        std::println("{}: {}", (*it)[1].str(), temperature);
        if (temperature > hottest) {
            hottest = temperature;
        }
    }
    std::println("hottest: {}", hottest);

    // Part C: format_no_copy drops everything the pattern did not match, so
    // only the replacement text ("7,91\n" ...) ends up in the result.
    const std::string csv{std::regex_replace(
        log_line, std::regex{R"(sensor-(\d+) temp=(\d+))"}, "$1,$2\n",
        std::regex_constants::format_no_copy)};
    std::print("{}", csv);

    return 0;
}

// Sorts a local copy so the caller's vector is never touched.
std::vector<int> top_n(const std::vector<int>& data, std::size_t n) {
    std::vector<int> sorted{data};
    std::ranges::sort(sorted, std::ranges::greater{});

    std::vector<int> top{};
    for (std::size_t i{0}; i < n && i < sorted.size(); ++i) {
        top.push_back(sorted[i]);
    }
    return top;
}

// O(log n) per lookup, but only because the caller promises ascending order.
bool is_registered(const std::vector<std::string>& sorted_ids, const std::string& id) {
    return std::ranges::binary_search(sorted_ids, id);
}

// The view is taken by value (it is just a pointer and a length) and only
// its window moves; the returned view points into the caller's own text.
std::string_view sensor_number(std::string_view name) {
    constexpr std::string_view prefix{"sensor-"};
    if (name.starts_with(prefix)) {
        name.remove_prefix(prefix.size());
    }
    return name;
}

// Right-aligns the numbers into fixed-width columns using the {:...} spec
// grammar, no manual padding. Returns a string, so it uses format, not print.
std::string format_row(std::string_view number, double reading, const std::string& status) {
    return std::format("{:>3} | {:^6} | {:>8.2f}", number, status, reading);
}

// floor<days> already yields a sys_days for "today"; target is converted to
// the same shape (a count of days since the epoch) so the two can be
// subtracted directly. year_month_day itself has no -.
long long days_until(std::chrono::year_month_day target) {
    const auto today{std::chrono::floor<std::chrono::days>(
        std::chrono::system_clock::now())};
    const std::chrono::sys_days target_days{target};

    return (target_days - today).count();
}

// regex_match needs the WHOLE id to fit, so the trailing-space and
// four-digit candidates fail without any extra anchors in the pattern.
bool is_valid_sensor_id(const std::string& id) {
    const std::regex pattern{R"(sensor-\d{1,3})"};
    return std::regex_match(id, pattern);
}
