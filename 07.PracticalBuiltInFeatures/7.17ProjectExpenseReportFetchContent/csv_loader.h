#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "report.h"

// Load and parse a CSV file into Expenses using the csv2 library instead
// of hand-splitting. This header is shared, byte for byte, by the
// vendored (7.16) and FetchContent (7.17) versions - only how csv2's
// headers reach the compiler differs, and that is a CMake concern.

struct LoadResult {
    std::vector<Expense> expenses{};
    std::size_t rows_seen{0};      // data rows the library handed us
    std::size_t skipped{0};        // rows that failed our own validation
    bool opened{false};            // false if the file could not be read
};

LoadResult load_expenses(const std::string& path);
