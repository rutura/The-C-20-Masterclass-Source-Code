#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iterator>
#include <optional>
#include <print>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "log_entry.h"

// The chapter 14 analyzer answered every question with a hand-made loop and
// the right container. This version answers the same questions with the
// algorithms and views of chapter 15, and prints the same report.

std::string read_file(const std::string& path) {
    std::ifstream file{path, std::ios::binary};
    if (!file) {
        throw std::runtime_error{"cannot open " + path + " (run rooster_generate first)"};
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

using Ranking = std::vector<std::pair<std::size_t, std::string_view>>;

// "Group the entries by a key, add up a value for each group, largest first."
// Every ranking of the report is this one function (a function template, 6.13;
// Key and Value are callables, 15.8):
//   - sort by the key (a PROJECTION)
//   - chunk_by cuts the sorted entries into one group per key (15.9)
//   - each group becomes (sum of the value, key)
//   - sort the groups, biggest first
template <typename Key, typename Value>
Ranking ranking_by(std::vector<LogEntry> items, Key key, Value value) {
    std::ranges::sort(items, {}, key);

    auto same_key{[&](const LogEntry& a, const LogEntry& b) { return std::invoke(key, a) == std::invoke(key, b); }};
    Ranking totals;
    for (auto group : items | std::views::chunk_by(same_key)) {
        auto values{group | std::views::transform(value)};
        totals.push_back({std::ranges::fold_left(values, std::size_t{0}, std::plus<>{}),
                          std::string_view{std::invoke(key, group.front())}});
    }
    std::ranges::sort(totals, std::ranges::greater{});
    return totals;
}

int main(int argc, char** argv) {
    auto started{std::chrono::steady_clock::now()};
    std::string path{argc > 1 ? argv[1] : "access.log"};

    // The entries point into this string, so it must stay alive (14.12).
    std::string text;
    try {
        text = read_file(path);
    }
    catch (const std::exception& error) {
        std::println("{}", error.what());
        return 1;
    }

    // ---- 1. Parsing, as one pipeline -----------------------------------------
    // text -> pieces between '\n' -> strings -> drop empty ones -> parse
    //      -> keep the parsed ones -> unwrap the optional -> into a vector
    // split gives, for a std::string, one subrange (a pair of iterators in one
    // object, 15.3) per piece between the newlines.
    using Piece = std::ranges::subrange<std::string::iterator>;

    auto lines{text
        | std::views::split('\n')
        | std::views::transform([](const Piece& piece) {
              std::string_view line{piece};
              if (line.ends_with('\r')) {
                  line.remove_suffix(1);
              }
              return line;
          })
        | std::views::filter([](std::string_view line) { return !line.empty(); })};

    using Parsed = std::optional<LogEntry>;
    auto entries{lines
        | std::views::transform(parse_line)
        | std::views::filter([](const Parsed& entry) { return entry.has_value(); })
        | std::views::transform([](const Parsed& entry) { return *entry; })
        | std::ranges::to<std::vector>()};

    // `lines` is only a recipe, so counting them walks the text a second time.
    auto line_count{static_cast<std::size_t>(std::ranges::distance(lines))};
    std::size_t total_bytes{std::ranges::fold_left(entries | std::views::transform(&LogEntry::bytes), std::size_t{0}, std::plus<>{})};
    std::println("{}: {} lines, {} requests, {} damaged lines, {:.1f} MB served\n",
                 path, line_count, entries.size(), line_count - entries.size(),
                 static_cast<double>(total_bytes) / 1'000'000.0);

    // ---- 2. Status codes: sort the codes, cut into runs of equal codes ------
    auto statuses{entries | std::views::transform(&LogEntry::status) | std::ranges::to<std::vector>()};
    std::ranges::sort(statuses);
    std::println("status codes");
    for (auto group : statuses | std::views::chunk_by(std::ranges::equal_to{})) {
        auto count{std::ranges::size(group)};
        std::println("  {}  {:6}  {:5.1f} %", group.front(), count,
                     100.0 * static_cast<double>(count) / static_cast<double>(entries.size()));
    }

    // ---- 3. Requests per hour: count the entries of each hour 0..23 -------
    auto per_hour{std::views::iota(0, 24)
        | std::views::transform([&](int hour) {
              return static_cast<std::size_t>(std::ranges::count_if(entries, [hour](const LogEntry& e) { return e.hour == hour; }));
          })
        | std::ranges::to<std::vector>()};
    std::size_t busiest{*std::ranges::max_element(per_hour)};
    std::size_t scale{busiest / 40 + 1};
    std::println("\nrequests per hour (each # is about {} requests)", scale);
    for (auto [hour, count] : std::views::enumerate(per_hour)) {
        std::println("  {:02}h {:5} {}", hour, count, std::string(count / scale, '#'));
    }

    // ---- 4. Rankings: one function, three questions -------------------------
    auto one{[](const LogEntry&) { return std::size_t{1}; }};

    std::println("\ntop 5 pages");
    for (const auto& [count, page] : ranking_by(entries, &LogEntry::path, one) | std::views::take(5)) {
        std::println("  {:6}  {}", count, page);
    }

    auto clients{ranking_by(entries, &LogEntry::client, one)};
    std::println("\ntop 5 clients (of {} different clients)", clients.size());
    for (const auto& [count, client] : clients | std::views::take(5)) {
        std::println("  {:6}  {}", count, client);
    }

    std::println("\nheaviest 3 pages by bytes served");
    for (const auto& [bytes, page] : ranking_by(entries, &LogEntry::path, &LogEntry::bytes) | std::views::take(3)) {
        std::println("  {:7.1f} MB  {}", static_cast<double>(bytes) / 1'000'000.0, page);
    }

    // ---- 5. Broken links: group by page, then by client inside each page ------
    auto missing{entries
        | std::views::filter([](const LogEntry& e) { return e.status == 404; })
        | std::ranges::to<std::vector>()};
    std::ranges::sort(missing, {}, [](const LogEntry& e) { return std::pair<std::string_view, std::string_view>{e.path, e.client}; });

    std::println("\nbroken links (404)");
    for (auto by_page : missing | std::views::chunk_by([](const LogEntry& a, const LogEntry& b) { return a.path == b.path; })) {
        auto different_clients{std::ranges::distance(
            by_page | std::views::chunk_by([](const LogEntry& a, const LogEntry& b) { return a.client == b.client; }))};
        std::println("  {:<26} {:5} hits from {:3} different clients",
                     by_page.front().path, std::ranges::size(by_page), different_clients);
    }

    auto elapsed{std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count()};
    std::println("\nwhole analysis: {:.1f} ms", elapsed);
    return 0;
}
