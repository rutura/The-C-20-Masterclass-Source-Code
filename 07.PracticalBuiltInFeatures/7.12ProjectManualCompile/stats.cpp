#include "stats.h"

#include <algorithm>
#include <numeric>

namespace station {

    double to_celsius(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }

    Summary summarize(const std::vector<double>& readings) {
        /*
        The [lowest, highest] syntax declares two names at once. 
        They bind to the members of the returned object in declaration order. 
        lowest gets .min and highest gets .max. The names are yours to choose. 
        You could have set up to calls for min and max, but them I wouldn't have
        gotten a change to teach you about structured bindings here. They were 
        introduced in C++ 17 and you will see them in a lot of modern C++ code out there.
        */
        const auto [lowest, highest] = std::ranges::minmax(readings);
        const double total{std::accumulate(readings.begin(), readings.end(), 0.0)};
        return Summary{lowest, highest, total / static_cast<double>(readings.size())};
    }

}   // namespace station
