#pragma once

#include <vector>

namespace station {

struct Summary {
    double lowest{};
    double highest{};
    double average{};
};

// A plain free function on purpose: its mangled name is the first one we
// will read inside the object files.
double to_celsius(double fahrenheit);

// Needs at least one reading. An empty vector has no lowest or average.
Summary summarize(const std::vector<double>& readings);

}   // namespace station
