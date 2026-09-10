#include <chrono>
#include <fstream>
#include <print>
#include <span>
#include <string>
#include <vector>

#include "report.h"

// PROJECT (version A): parse the CSV BY HAND - no third-party library.
//
// One row per line, fields separated by commas. Simple enough to split
// ourselves with std::string / std::string_view (see parse_expense_line
// in report.cpp). Versions 7.16 and 7.17 swap this loader for the csv2
// library; report.h / report.cpp stay exactly the same.

int main(int argc, char* argv[]) {
    std::span<char*> args{argv, static_cast<std::size_t>(argc)};

    // The data file is argv[1], defaulting to expenses.csv next to the exe.
    std::string path{args.size() >= 2 ? args[1] : "expenses.csv"};

    // --- phase 1: read the file into memory ---
    auto t0{std::chrono::steady_clock::now()};

    std::ifstream in{path};
    if (!in) {
        std::println("could not open {}", path);
        std::println("usage: {} [path-to-csv]", args[0]);
        return 1;
    }

    std::vector<std::string> lines{};
    std::string line{};
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {   // tolerate CRLF files
            line.pop_back();
        }
        lines.push_back(line);
    }

    auto t1{std::chrono::steady_clock::now()};

    // --- phase 2: parse each line into an Expense ---
    std::vector<Expense> expenses{};
    int skipped{0};
    for (const std::string& raw : lines) {
        if (auto e{parse_expense_line(raw)}) {
            expenses.push_back(*e);
        } else if (!raw.empty() && !raw.starts_with("date,")) {
            ++skipped;
        }
    }

    auto t2{std::chrono::steady_clock::now()};

    // --- phase 3: aggregate and report ---
    auto totals{totals_by_category(expenses)};
    auto t3{std::chrono::steady_clock::now()};

    std::println("Expense report for {}", path);
    std::println("{} lines read, {} expenses parsed, {} malformed lines skipped\n",
                 lines.size(), expenses.size(), skipped);

    print_bar_chart(totals);

    // --- timing summary ---
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    std::println("\ntiming:");
    std::println("  read file : {}", duration_cast<microseconds>(t1 - t0));
    std::println("  parse     : {}", duration_cast<microseconds>(t2 - t1));
    std::println("  aggregate : {}", duration_cast<microseconds>(t3 - t2));
    std::println("  total     : {}", duration_cast<microseconds>(t3 - t0));

    return 0;
}
