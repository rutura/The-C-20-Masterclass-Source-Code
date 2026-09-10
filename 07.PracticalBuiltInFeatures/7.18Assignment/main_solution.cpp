#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <numeric>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 7 assignment - SOLUTION

    Each exercise's statement is repeated above its solution. Same rules
    as main.cpp: std::print / std::println only, brace-init everything,
    std:: everywhere.
*/

inline constexpr std::array<std::string_view, 6> raw_records{
    "2025-03-01,roof,12.5",
    "2025-03-02,roof,14.0",
    "2025-03-03,roof,9.5",
    "2025-03-01,yard,11.0",
    "2025-03-02,yard,broken-sensor",
    "2025-03-03,yard,13.5",
};

using Temperature = double;

// --- Exercise 2 ---
std::optional<Temperature> parse_value(std::string_view text) {
    Temperature value{};
    auto [ptr, ec]{std::from_chars(text.data(), text.data() + text.size(), value)};
    if (ec != std::errc{} || ptr != text.data() + text.size()) {
        return std::nullopt;
    }
    return value;
}

// --- Exercise 3 ---
struct Record {
    std::string date{};
    std::string station{};
    Temperature value{};
};

std::optional<Record> parse_record(std::string_view line) {
    std::size_t c1{line.find(',')};
    if (c1 == std::string_view::npos) {
        return std::nullopt;
    }
    std::size_t c2{line.find(',', c1 + 1)};
    if (c2 == std::string_view::npos) {
        return std::nullopt;
    }
    if (line.find(',', c2 + 1) != std::string_view::npos) {
        return std::nullopt;                    // more than three fields
    }

    std::string_view date{line.substr(0, c1)};
    std::string_view station{line.substr(c1 + 1, c2 - c1 - 1)};
    std::string_view value_text{line.substr(c2 + 1)};

    auto value{parse_value(value_text)};
    if (!value) {
        return std::nullopt;
    }

    return Record{std::string{date}, std::string{station}, *value};
}

// --- Exercise 5 ---
enum class Station : std::uint8_t { Roof, Yard, Unknown };

Station station_from_text(std::string_view text) {
    if (text == "roof") {
        return Station::Roof;
    }
    if (text == "yard") {
        return Station::Yard;
    }
    return Station::Unknown;
}

std::string_view station_name(Station s) {
    using enum Station;
    switch (s) {
        case Roof:    return "ROOF";
        case Yard:    return "YARD";
        case Unknown: return "UNKNOWN";
    }
    return "UNKNOWN";
}

// --- Exercise 7 ---
std::optional<std::chrono::year_month_day> parse_date(std::string_view text) {
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') {
        return std::nullopt;
    }
    int y{};
    int m{};
    int d{};
    auto slice_ok = [](std::from_chars_result r, const char* end) {
        return r.ec == std::errc{} && r.ptr == end;
    };
    if (!slice_ok(std::from_chars(text.data(), text.data() + 4, y), text.data() + 4) ||
        !slice_ok(std::from_chars(text.data() + 5, text.data() + 7, m), text.data() + 7) ||
        !slice_ok(std::from_chars(text.data() + 8, text.data() + 10, d), text.data() + 10)) {
        return std::nullopt;
    }
    std::chrono::year_month_day ymd{
        std::chrono::year{y}, std::chrono::month{static_cast<unsigned>(m)},
        std::chrono::day{static_cast<unsigned>(d)}};
    return ymd.ok() ? std::optional{ymd} : std::nullopt;
}

int main() {
    /*
        Exercise 1 - a fixed-size std::array of labels
    */
    std::println("--- Exercise 1: station list ---");
    std::array<std::string_view, 2> stations{"roof", "yard"};
    for (int i{0}; std::string_view s : stations) {
        std::println("station {}: {}", i, s);
        ++i;
    }

    /*
        Exercise 2 - Temperature type alias + parse_value()
    */
    std::println("\n--- Exercise 2: parse_value ---");
    std::println("parse_value(\"13.5\")          -> {}",
                 parse_value("13.5").value_or(0.0));
    std::println("parse_value(\"broken-sensor\") -> {}",
                 parse_value("broken-sensor").has_value() ? "parsed" : "(none)");

    /*
        Exercise 3 - split a record with std::string_view
    */
    std::println("\n--- Exercise 3: parse_record ---");
    std::vector<Record> records{};
    int rejected{0};
    for (std::string_view line : raw_records) {
        if (auto r{parse_record(line)}) {
            records.push_back(*r);
        } else {
            ++rejected;
        }
    }
    std::println("parsed {} records, {} rejected", records.size(), rejected);

    /*
        Exercise 4 - min / max / average with the algorithms
    */
    std::println("\n--- Exercise 4: summary stats ---");
    std::vector<Temperature> values{};
    for (const Record& r : records) {
        values.push_back(r.value);
    }
    double sum{std::accumulate(values.begin(), values.end(), 0.0)};
    std::println("low {}, high {}, average {:.1f}",
                 *std::ranges::min_element(values),
                 *std::ranges::max_element(values),
                 sum / values.size());

    /*
        Exercise 5 - Station enum + using enum
    */
    std::println("\n--- Exercise 5: station enum ---");
    for (const Record& r : records) {
        std::println("{}  {}  {}", r.date,
                     station_name(station_from_text(r.station)), r.value);
    }

    /*
        Exercise 6 - sort records, newest value first
    */
    std::println("\n--- Exercise 6: sort by value ---");
    std::vector<Record> sorted{records};
    std::ranges::sort(sorted, [](const Record& a, const Record& b) {
        return a.value > b.value;
    });
    for (const Record& r : sorted) {
        std::println("{}  {}  {}", r.date, r.station, r.value);
    }

    /*
        Exercise 7 - which day is the record from? (<chrono>)
    */
    std::println("\n--- Exercise 7: record dates ---");
    for (const Record& r : records) {
        if (auto ymd{parse_date(r.date)}) {
            std::chrono::weekday wd{std::chrono::sys_days{*ymd}};
            std::println("{:%Y-%m-%d} is a {:%a}", *ymd, wd);
        }
    }

    return 0;
}
