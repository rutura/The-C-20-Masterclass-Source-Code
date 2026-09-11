#include <print>
#include <array>

// --- by value: the whole array gets COPIED --------------------------------
// 6.10 showed that const on a by-value int parameter only protects a copy
// the function already owns - the caller was never at risk either way.
// The same is true for a std::array, but the COST is no longer nothing:
// copying five ints is cheap; copying a much larger array would not be.
void report_by_value(std::array<int, 5> readings) {
    readings[0] = -1;   // only touches this function's own copy
    std::print("inside report_by_value (after editing the copy): ");
    for (int reading : readings) {
        std::print("{} ", reading);
    }
    std::println("");
}

// --- by reference: an ALIAS for the caller's own array ---------------------
// No copy. Whatever this function writes through readings lands directly
// on the caller's array - the right tool when a function's whole job is
// to mutate the caller's data in place.
void reset_readings(std::array<int, 5>& readings) {
    for (int& reading : readings) {
        reading = 0;
    }
}

// --- by const reference: an alias, but a read-only one ---------------------
// No copy, and the compiler enforces that this function cannot write
// through readings - the promise a reference parameter actually needs
// const for (6.10). This is the shape a "just report what's there"
// function should have: cheap, and provably unable to disturb the data
// it is reporting on.
void report_by_const_ref(const std::array<int, 5>& readings) {
    std::print("readings: ");
    for (int reading : readings) {
        std::print("{} ", reading);
    }
    std::println("");
}

int main() {

    std::array<int, 5> sensor_readings{68, 71, 69, 72, 70};

    // By value
    std::println("--- by value ---");
    report_by_value(sensor_readings);
    std::print("sensor_readings after report_by_value (unchanged): ");
    for (int reading : sensor_readings) {
        std::print("{} ", reading);
    }
    std::println("");

    // By reference
    std::println("\n--- by reference ---");
    report_by_const_ref(sensor_readings);
    reset_readings(sensor_readings);
    std::print("sensor_readings after reset_readings (changed): ");
    for (int reading : sensor_readings) {
        std::print("{} ", reading);
    }
    std::println("");

    // By const reference
    std::println("\n--- by const reference ---");
    report_by_const_ref(sensor_readings);

    return 0;
}
