#include <print>
#include <vector>

#include "report.h"
#include "stats.h"

// PROJECT: the same program as 7.12, but stats.cpp and report.cpp are now
// bundled into a static library, and main.cpp is linked against that archive
// instead of against loose object files.

int main() {

    // Fahrenheit readings from one imaginary weather station (chapter 7 theme).
    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const station::Summary summary{station::summarize(readings)};

    std::println("{}", station::format_report("sensor-12", summary));

    return 0;
}
