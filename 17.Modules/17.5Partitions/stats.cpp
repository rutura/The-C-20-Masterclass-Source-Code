module;

#include <cmath>
#include <vector>

module forecast;                   // the implementation unit of the whole module

import :detail;                    // available here, not to importers

double mean_of(const Series& series) {
    if (series.readings.empty()) {
        return 0.0;
    }
    double total{0.0};
    for (const Reading& reading : series.readings) {
        total += reading.celsius;
    }
    return total / static_cast<double>(series.readings.size());
}

double spread_of(const Series& series) {
    if (series.readings.empty()) {
        return 0.0;
    }
    double mean{mean_of(series)};
    double total{0.0};
    for (const Reading& reading : series.readings) {
        total += square(reading.celsius - mean);
    }
    return std::sqrt(total / static_cast<double>(series.readings.size()));
}
