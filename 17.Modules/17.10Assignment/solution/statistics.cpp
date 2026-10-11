module;

#include <algorithm>
#include <numeric>
#include <vector>

module statistics;

double mean_of(const std::vector<double>& values) {
    if (values.empty()) {
        return 0.0;
    }
    return std::accumulate(values.begin(), values.end(), 0.0) / static_cast<double>(values.size());
}

double largest_of(const std::vector<double>& values) {
    if (values.empty()) {
        return 0.0;
    }
    return *std::ranges::max_element(values);
}
