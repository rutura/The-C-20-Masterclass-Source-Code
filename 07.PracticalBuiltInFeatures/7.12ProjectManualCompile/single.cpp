#include <numeric>
#include <print>
#include <vector>

// PROJECT, part 1: one source file, nothing to link against. Small enough to
// compile two ways (source -> object -> executable, or source -> executable)
// and to open the object file afterwards.

int main() {

    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const double total{std::accumulate(readings.begin(), readings.end(), 0.0)};

    std::println("average: {:.1f} F", total / static_cast<double>(readings.size()));

    return 0;
}
