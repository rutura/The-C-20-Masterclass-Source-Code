#pragma once

#include <vector>

#include "station_export.h"

namespace station {

struct Summary {
    double lowest{};
    double highest{};
    double average{};
};

// A plain free function, so the verbose build output stays easy to read.
// STATION_EXPORT comes from station_export.h, which CMake generates into the
// build folder (generate_export_header), instead of the hand-written macro of 7.14.
STATION_EXPORT double to_celsius(double fahrenheit);

// Needs at least one reading. An empty vector has no lowest or average.
STATION_EXPORT Summary summarize(const std::vector<double>& readings);

}   // namespace station
