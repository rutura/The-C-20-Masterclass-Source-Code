#include <numeric>
#include <print>
#include <vector>

// PROJECT: the single-file program. The notes build it in two steps (compile
// to an object file, then link) and in one step (the compiler driver runs
// both), then compare the two executables. It calls no other source file, so
// the linker has nothing to match up.

int main() {

    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const double total{std::accumulate(readings.begin(), readings.end(), 0.0)};

    std::println("average: {:.1f} F", total / static_cast<double>(readings.size()));

    return 0;
}
