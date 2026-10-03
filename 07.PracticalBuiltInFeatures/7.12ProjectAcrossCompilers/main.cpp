#include <print>
#include <vector>

#include "average.h"

// average() is NOT defined in this file - it is compiled separately, into
// its own library (see CMakeLists.txt), and only brought in by the linker.
// NOTES.md is the point of this lecture: what that library actually looks
// like on disk, and what has to be true of it for the linker to accept it.
int main() {
    std::vector<double> sensor_readings{68.0, 72.5, 59.0, 81.5};
    std::println("average(sensor_readings) = {}", average(sensor_readings));
    return 0;
}
