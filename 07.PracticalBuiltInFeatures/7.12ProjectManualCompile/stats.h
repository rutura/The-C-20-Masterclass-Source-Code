#pragma once

#include <vector>

namespace station {

struct Summary {
    double lowest{};
    double highest{};
    double average{};
};

// A plain free function on purpose: stats.cpp defines it and report.cpp only
// uses it, so its mangled name shows up as defined in one object file and as
// undefined in the other. The notes read that pair with dumpbin (MSVC) and nm
// (MinGW and Linux).
double to_celsius(double fahrenheit);

// Needs at least one reading. An empty vector has no lowest or average.
Summary summarize(const std::vector<double>& readings);

}   // namespace station
