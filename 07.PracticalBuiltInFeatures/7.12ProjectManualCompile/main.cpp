#include <print>
#include <vector>

#include "report.h"
#include "stats.h"

// PROJECT: build this program by hand, with no CMake and no IDE.
//
// Three translation units: main.cpp, stats.cpp and report.cpp. Each one is
// compiled to its own object file, and the linker joins them. The notes walk
// through the exact commands for MSVC, MinGW GCC, MinGW Clang and Linux.

int main() {

    // Fahrenheit readings from one imaginary weather station (chapter 7 theme).
    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const station::Summary summary{station::summarize(readings)};

    std::println("{}", station::format_report("sensor-12", summary));

    return 0;
}
