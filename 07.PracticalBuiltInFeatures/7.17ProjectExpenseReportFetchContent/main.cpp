#include <chrono>
#include <print>
#include <span>
#include <string>

#include "csv_loader.h"
#include "report.h"

// PROJECT (version B): the CSV parsing is done by the csv2 library,
// VENDORED - its headers are committed under vendor/csv2/ and compiled
// from source here. report.h / report.cpp are unchanged from version A;
// only the loader (csv_loader.cpp) is different, and it still finishes by
// calling make_expense() from report.h.

int main(int argc, char* argv[]) {
    std::span<char*> args{argv, static_cast<std::size_t>(argc)};
    std::string path{args.size() >= 2 ? args[1] : "expenses.csv"};

    // --- phase 1+2: read and parse, via csv2 ---
    auto t0{std::chrono::steady_clock::now()};
    LoadResult loaded{load_expenses(path)};
    auto t1{std::chrono::steady_clock::now()};

    if (!loaded.opened) {
        std::println("could not open {}", path);
        std::println("usage: {} [path-to-csv]", args[0]);
        return 1;
    }

    // --- phase 3: aggregate and report ---
    auto totals{totals_by_category(loaded.expenses)};
    auto t2{std::chrono::steady_clock::now()};

    std::println("Expense report for {}", path);
    std::println("{} data rows, {} expenses parsed, {} rows skipped\n",
                 loaded.rows_seen, loaded.expenses.size(), loaded.skipped);

    print_bar_chart(totals);

    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    std::println("\ntiming:");
    std::println("  load + parse : {}", duration_cast<microseconds>(t1 - t0));
    std::println("  aggregate    : {}", duration_cast<microseconds>(t2 - t1));
    std::println("  total        : {}", duration_cast<microseconds>(t2 - t0));

    return 0;
}
