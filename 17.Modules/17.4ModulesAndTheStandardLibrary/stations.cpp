// The global module fragment again. Every module unit includes what IT uses:
// the includes of the interface file do not carry over to this file, even
// though this file sees the interface's declarations. (Delete <string> and
// <vector> below to read the error: std::string is "not visible" here.)
// <algorithm> and <numeric> are needed only by this file, so importers never get them.
module;

#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

// This file implements the module `stations`. It sees everything in the
// interface, exported or not, without importing or including anything.
module stations;

// Not exported, not in the interface: private to the module.
static bool has_readings(const Station& station) {
    return !station.readings.empty();
}

double mean_of(const Station& station) {
    if (!has_readings(station)) {
        return 0.0;
    }
    double total{std::accumulate(station.readings.begin(), station.readings.end(), 0.0)};
    return total / static_cast<double>(station.readings.size());
}

double largest_of(const Station& station) {
    if (!has_readings(station)) {
        return 0.0;
    }
    return *std::ranges::max_element(station.readings);
}

Station make_station(std::string name, std::vector<double> readings) {
    return Station{std::move(name), std::move(readings)};
}

bool is_empty(const Station& station) {
    return !has_readings(station);
}
