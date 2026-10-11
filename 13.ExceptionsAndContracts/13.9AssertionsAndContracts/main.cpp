#include <cassert>
#include <print>
#include <type_traits>
#include <vector>

struct Reading {
    int sensor_id;
    double value;
};

// static_assert is checked by the COMPILER, costs nothing at run time, and
// turns a silent assumption into a build error the day it stops being true.
static_assert(std::is_trivially_copyable_v<Reading>, "Readings are copied byte for byte into the log file");
static_assert(sizeof(int) >= 4);

// assert is checked at RUN time, and only in builds without NDEBUG. CMake's
// Release configuration defines NDEBUG, so the check vanishes there. Use it for
// "this can never happen unless the program itself has a bug".
double average(const std::vector<Reading>& readings) {
    assert(!readings.empty() && "average of no readings");

    double total{0.0};
    for (const auto& reading : readings) {
        total += reading.value;
    }
    return total / static_cast<double>(readings.size());
}

// Do NOT hide work inside an assert. In a Release build the whole expression,
// side effects included, is gone:
//     assert(log.try_open());       // the file is never opened in Release

int main(int argc, char**) {

    std::vector<Reading> readings{{1, 20.5}, {2, 21.5}, {3, 22.0}};
    std::println("average: {:.2f}", average(readings));

    if (argc > 1) {
        std::println("calling average() on an empty vector...");
        std::println("average: {}", average({}));
    }

    // assert is for bugs, exceptions are for conditions that can legitimately
    // happen. An empty vector from user input is a condition, not a bug, so
    // real code would validate the input before getting here.
    return 0;
}
