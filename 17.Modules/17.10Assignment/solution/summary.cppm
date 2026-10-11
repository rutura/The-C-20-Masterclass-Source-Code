export module summary;

import std;

export std::string summary_of(const std::vector<double>& values) {
    std::vector<double> sorted{values};
    std::ranges::sort(sorted);
    double total{std::accumulate(sorted.begin(), sorted.end(), 0.0)};
    return std::format("lowest {}, highest {}, mean {:.2f}", sorted.front(), sorted.back(),
                       total / static_cast<double>(sorted.size()));
}
