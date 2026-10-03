#include "average.h"

double average(const std::vector<double>& readings) {
    double total{0.0};
    for (double reading : readings) {
        total += reading;
    }
    return total / static_cast<double>(readings.size());
}
