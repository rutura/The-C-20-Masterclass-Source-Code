#include "stats.h"

#include <algorithm>
#include <numeric>

namespace station {

double to_celsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

Summary summarize(const std::vector<double>& readings) {
    const auto [lowest, highest] = std::ranges::minmax(readings);
    const double total{std::accumulate(readings.begin(), readings.end(), 0.0)};
    return Summary{lowest, highest, total / static_cast<double>(readings.size())};
}

}   // namespace station
