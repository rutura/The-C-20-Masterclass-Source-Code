#pragma once

#include <vector>

#include "station_api.h"

namespace station {

struct Summary {
    double lowest{};
    double highest{};
    double average{};
};

// A plain free function on purpose: its mangled name is one of the three the
// notes read in the library's export table (dumpbin /exports, objdump -p on
// Windows, nm -D on Linux).
STATION_API double to_celsius(double fahrenheit);

// Needs at least one reading. An empty vector has no lowest or average.
STATION_API Summary summarize(const std::vector<double>& readings);

}   // namespace station
