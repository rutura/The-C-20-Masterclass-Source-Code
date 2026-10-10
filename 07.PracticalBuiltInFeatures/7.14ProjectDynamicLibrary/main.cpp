#include <print>
#include <vector>

#include "report.h"
#include "stats.h"

// PROJECT: the same program again, but now stats.cpp and report.cpp live in a
// dynamic library. main.cpp is not linked to their code: the finished program
// finds the library and loads it when it starts.

int main() {

    // Fahrenheit readings from one imaginary weather station (chapter 7 theme).
    const std::vector<double> readings{68.0, 72.5, 59.0, 81.0, 90.5, 55.0, 77.0, 64.5};

    const station::Summary summary{station::summarize(readings)};

    std::println("{}", station::format_report("sensor-12", summary));

    return 0;
}
