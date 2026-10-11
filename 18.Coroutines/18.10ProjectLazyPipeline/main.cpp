#include <algorithm>
#include <array>
#include <cstddef>
#include <format>
#include <fstream>
#include <generator>
#include <optional>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "log_entry.h"
#include "scheduler.h"
#include "task.h"

// The chapter 14 and 15 analyzers read the whole file into one string and
// worked on it. This version never holds the file. It is built from two kinds
// of coroutines:
//
//   GENERATORS  form the pipeline:   lines  ->  requests  ->  (filter)
//               each stage pulls one item from the stage before it, only
//               when the stage after it asks
//   TASKS       are the jobs:        three analyses that run on one thread,
//               taking turns in a Scheduler (18.9)

// A request that owns its text. In 15.11 the text fields were string_views
// into the file's buffer. A line that has been read and forgotten has no
// buffer to point into, so each request keeps its own copies.
struct Request {
    std::string client;
    std::string method;
    std::string path;
    int hour;
    int status;
    std::size_t bytes;
};

// ---- Stage 1: the lines of a file, one at a time ------------------------------------
// `lines_read` counts how many lines were really pulled (a reference: it
// belongs to the caller and outlives this coroutine, 18.8).
std::generator<std::string> lines(std::string path, std::size_t& lines_read) {
    std::ifstream file{path};
    if (!file) {
        throw std::runtime_error{"cannot open " + path + " (run rooster_generate first)"};
    }
    std::string line;
    while (std::getline(file, line)) {
        ++lines_read;
        co_yield line;
    }
}

// ---- Stage 2: parse each line; skip the damaged ones --------------------------------
// The previous stage is a PARAMETER taken by value: a generator is move-only,
// the call site moves it in, and the frame keeps it alive (18.8).
std::generator<Request> requests(std::generator<std::string> source, std::size_t& damaged) {
    for (const std::string& line : source) {
        std::optional<LogEntry> entry{parse_line(line)};
        if (!entry) {
            ++damaged;
            continue;
        }
        co_yield Request{std::string{entry->client}, std::string{entry->method}, std::string{entry->path},
                         entry->hour, entry->status, entry->bytes};
    }
}

// Stage 3 needs no coroutine: a generator is a range (18.3), so the views of
// chapter 15 attach to it.
bool is_error(const Request& request) {
    return request.status >= 400;
}

// ---- The jobs -----------------------------------------------------------------------
// The jobs write their report into a string that main() owns, and main()
// prints the reports after run() has returned, in a fixed order. The
// reference is safe: run() finishes while main()'s variables are alive.

using Counts = std::vector<std::pair<std::string, std::size_t>>;

// Largest first; the name breaks ties, so the report never depends on hash order.
Counts top_of(const std::unordered_map<std::string, std::size_t>& totals, std::size_t how_many) {
    Counts rows{totals.begin(), totals.end()};
    std::ranges::sort(rows, [](const auto& a, const auto& b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    });
    if (rows.size() > how_many) {
        rows.resize(how_many);
    }
    return rows;
}

// The same shape for every job: pull requests, update some state, and after
// every `batch` requests give the other jobs a turn.
Task<void> top_pages(Scheduler& scheduler, std::string path, std::size_t batch, std::string& report) {
    std::size_t lines_read{0};
    std::size_t damaged{0};
    std::unordered_map<std::string, std::size_t> hits;
    std::size_t seen{0};

    for (const Request& request : requests(lines(path, lines_read), damaged)) {
        ++hits[request.path];
        if (++seen % batch == 0) {
            std::println("[top pages]       {} requests so far", seen);
            co_await scheduler.yield_now();
        }
    }
    report += std::format("top pages ({} requests, {} damaged lines skipped)\n", seen, damaged);
    for (const auto& [page, count] : top_of(hits, 5)) {
        report += std::format("  {:>6}  {}\n", count, page);
    }
}

Task<void> error_hours(Scheduler& scheduler, std::string path, std::size_t batch, std::string& report) {
    std::size_t lines_read{0};
    std::size_t damaged{0};
    std::array<std::size_t, 24> errors_by_hour{};
    std::size_t seen{0};
    std::size_t errors{0};
    // Errors are rarer than requests, so this job takes turns more often.
    std::size_t error_batch{std::max<std::size_t>(batch / 10, 1)};

    // Stage 3, the filter, is a view on the generator.
    for (const Request& request : requests(lines(path, lines_read), damaged) | std::views::filter(is_error)) {
        ++errors_by_hour[static_cast<std::size_t>(request.hour)];
        ++errors;
        if (++seen % error_batch == 0) {
            std::println("[error hours]     {} errors so far", seen);
            co_await scheduler.yield_now();
        }
    }
    std::unordered_map<std::string, std::size_t> by_hour;
    for (std::size_t hour{0}; hour < errors_by_hour.size(); ++hour) {
        if (errors_by_hour[hour] > 0) {
            by_hour[std::format("{:02}:00", hour)] = errors_by_hour[hour];
        }
    }
    report += std::format("busiest hours for errors ({} errors in {} lines)\n", errors, lines_read);
    for (const auto& [hour, count] : top_of(by_hour, 3)) {
        report += std::format("  {:>6}  {}\n", count, hour);
    }
}

Task<void> heavy_clients(Scheduler& scheduler, std::string path, std::size_t batch, std::string& report) {
    std::size_t lines_read{0};
    std::size_t damaged{0};
    std::unordered_map<std::string, std::size_t> bytes_by_client;
    std::size_t seen{0};

    for (const Request& request : requests(lines(path, lines_read), damaged)) {
        bytes_by_client[request.client] += request.bytes;
        if (++seen % batch == 0) {
            std::println("[heavy clients]   {} requests so far", seen);
            co_await scheduler.yield_now();
        }
    }
    report += "clients that downloaded the most (bytes)\n";
    for (const auto& [client, bytes] : top_of(bytes_by_client, 3)) {
        report += std::format("  {:>10}  {}\n", bytes, client);
    }
}

int main(int argc, char** argv) {
    std::string path{argc > 1 ? argv[1] : "access.log"};
    std::size_t batch{argc > 2 ? static_cast<std::size_t>(std::stoul(argv[2])) : 5'000};

    try {
        // ---- Laziness: stop early and the rest of the file is never read ----------
        std::println("--- the first three server errors");
        std::size_t lines_read{0};
        std::size_t damaged{0};
        auto first_errors{requests(lines(path, lines_read), damaged)
            | std::views::filter(is_error)
            | std::views::take(3)};
        for (const Request& request : first_errors) {
            std::println("{} {} {} -> {}", request.client, request.method, request.path, request.status);
        }
        std::println("pulled {} lines out of the file to find them", lines_read);

        // ---- Three jobs, one thread ------------------------------------------------
        std::println("\n--- three analyses taking turns");
        Scheduler scheduler;
        std::string pages_report;
        std::string hours_report;
        std::string clients_report;
        scheduler.spawn(top_pages(scheduler, path, batch, pages_report));
        scheduler.spawn(error_hours(scheduler, path, batch, hours_report));
        scheduler.spawn(heavy_clients(scheduler, path, batch, clients_report));
        scheduler.run();

        std::println("\n--- results");
        std::print("{}\n{}\n{}", pages_report, hours_report, clients_report);
    }
    catch (const std::exception& error) {
        std::println("{}", error.what());
        return 1;
    }
    return 0;
}
