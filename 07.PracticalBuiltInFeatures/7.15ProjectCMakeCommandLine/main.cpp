#include <print>
#include <vector>

#include "report.h"
#include "stats.h"

// PROJECT: the same program, built the way real projects are built: CMake
// reads CMakeLists.txt, generates the compiler and linker commands you typed by
// hand in 7.12 to 7.14, and runs them. This project is about driving CMake from
// the command line, not about the C++.

int main() {

    // Fahrenheit readings from one imaginary weather station (chapter 7 theme).
    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const station::Summary summary{station::summarize(readings)};

    std::println("{}", station::format_report("sensor-12", summary));

    return 0;
}
