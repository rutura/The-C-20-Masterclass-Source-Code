#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iterator>
#include <map>
#include <print>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "log_entry.h"

// The N entries with the highest count, largest first. Works for any map from
// a name to a number (std::map and std::unordered_map alike). A small
// SMALLEST-first heap of size N (14.8) keeps the best N seen so far, so the
// cost is O(M log N) for M entries, and the whole table is never sorted.
template <typename Counts>
std::vector<std::pair<std::size_t, std::string_view>> top_n(const Counts& counts, std::size_t n) {
    using Entry = std::pair<std::size_t, std::string_view>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<>> heap;
    for (const auto& [name, count] : counts) {
        heap.push({count, name});
        if (heap.size() > n) {
            heap.pop();
        }
    }
    std::vector<Entry> result;
    while (!heap.empty()) {
        result.push_back(heap.top());
        heap.pop();
    }
    std::ranges::reverse(result);
    return result;
}

std::string read_file(const std::string& path) {
    std::ifstream file{path, std::ios::binary};
    if (!file) {
        throw std::runtime_error{"cannot open " + path + " (run rooster_generate first)"};
    }
    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

template <typename Work>
double milliseconds(Work&& work) {
    auto start{std::chrono::steady_clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
}

int main(int argc, char** argv) {
    std::string path{argc > 1 ? argv[1] : "access.log"};

    // The entries point into this string, so it must stay alive as long as they are used.
    std::string text;
    try {
        text = read_file(path);
    }
    catch (const std::exception& error) {
        std::println("{}", error.what());
        return 1;
    }

    // ---- 1. Parse every line into a vector of entries ------------------------
    std::vector<LogEntry> entries;
    std::size_t malformed{0};
    std::size_t line_count{0};
    for (std::size_t start{0}; start < text.size();) {
        std::size_t end{text.find('\n', start)};
        if (end == std::string::npos) {
            end = text.size();
        }
        ++line_count;
        std::string_view line{std::string_view{text}.substr(start, end - start)};
        if (line.ends_with('\r')) {
            line.remove_suffix(1);                    // a log that went through Windows may end lines with \r\n
        }
        if (auto entry{parse_line(line)}) {
            entries.push_back(*entry);
        } else {
            ++malformed;
        }
        start = end + 1;
    }

    std::size_t total_bytes{0};
    for (const auto& entry : entries) {
        total_bytes += entry.bytes;
    }
    std::println("{}: {} lines, {} requests, {} damaged lines, {:.1f} MB served\n",
                 path, line_count, entries.size(), malformed, static_cast<double>(total_bytes) / 1'000'000.0);

    // ---- 2. Status codes: a std::map, so they come out in numeric order ------
    std::map<int, std::size_t> by_status;
    for (const auto& entry : entries) {
        ++by_status[entry.status];
    }
    std::println("status codes");
    for (const auto& [status, count] : by_status) {
        std::println("  {}  {:6}  {:5.1f} %", status, count,
                     100.0 * static_cast<double>(count) / static_cast<double>(entries.size()));
    }

    // ---- 3. Requests per hour: the hours are 0 to 23, so a plain array ------
    std::array<std::size_t, 24> by_hour{};
    for (const auto& entry : entries) {
        ++by_hour.at(static_cast<std::size_t>(entry.hour));
    }
    std::size_t busiest{*std::ranges::max_element(by_hour)};
    std::println("\nrequests per hour (each # is about {} requests)", busiest / 40 + 1);
    for (std::size_t hour{0}; hour < by_hour.size(); ++hour) {
        std::println("  {:02}h {:5} {}", hour, by_hour[hour], std::string(by_hour[hour] / (busiest / 40 + 1), '#'));
    }

    // ---- 4. Counting by name: unordered_map, then the top 5 -----------------
    std::unordered_map<std::string_view, std::size_t> by_page;
    std::unordered_map<std::string_view, std::size_t> by_client;
    std::unordered_map<std::string_view, std::size_t> bytes_by_page;
    for (const auto& entry : entries) {
        ++by_page[entry.path];
        ++by_client[entry.client];
        bytes_by_page[entry.path] += entry.bytes;
    }

    std::println("\ntop 5 pages");
    for (const auto& [count, page] : top_n(by_page, 5)) {
        std::println("  {:6}  {}", count, page);
    }
    std::println("\ntop 5 clients (of {} different clients)", by_client.size());
    for (const auto& [count, client] : top_n(by_client, 5)) {
        std::println("  {:6}  {}", count, client);
    }
    std::println("\nheaviest 3 pages by bytes served");
    for (const auto& [bytes, page] : top_n(bytes_by_page, 3)) {
        std::println("  {:7.1f} MB  {}", static_cast<double>(bytes) / 1'000'000.0, page);
    }

    // ---- 5. Grouping: which clients hit each missing page? -------------------
    // A map of sets: the map is sorted by page, each set holds distinct clients.
    std::map<std::string_view, std::unordered_set<std::string_view>> clients_per_missing;
    std::map<std::string_view, std::size_t> missing_hits;
    for (const auto& entry : entries) {
        if (entry.status == 404) {
            clients_per_missing[entry.path].insert(entry.client);
            ++missing_hits[entry.path];
        }
    }
    std::println("\nbroken links (404)");
    for (const auto& [page, clients] : clients_per_missing) {
        std::println("  {:<26} {:5} hits from {:3} different clients", page, missing_hits[page], clients.size());
    }

    // ---- 6. Does the container choice matter? (14.11) ----------------------
    // Count the pages again with an ordered map and with a hash table.
    std::map<std::string_view, std::size_t> ordered_counts;
    std::unordered_map<std::string_view, std::size_t> hashed_counts;
    double ordered_ms{milliseconds([&] {
        for (const auto& entry : entries) {
            ++ordered_counts[entry.path];
        }
    })};
    double hashed_ms{milliseconds([&] {
        for (const auto& entry : entries) {
            ++hashed_counts[entry.path];
        }
    })};
    std::println("\ncounting {} pages: std::map {:.2f} ms, std::unordered_map {:.2f} ms (same result: {})",
                 entries.size(), ordered_ms, hashed_ms, ordered_counts.size() == hashed_counts.size());
    return 0;
}
