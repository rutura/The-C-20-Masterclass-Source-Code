#pragma once

#include <vector>

#include "station_export.h"

namespace station {

struct Summary {
    double lowest{};
    double highest{};
    double average{};
};

// A plain free function on purpose: its mangled name is the first one we
// will read inside the object files.
STATION_EXPORT double to_celsius(double fahrenheit);

// Needs at least one reading. An empty vector has no lowest or average.
STATION_EXPORT Summary summarize(const std::vector<double>& readings);

}   // namespace station
