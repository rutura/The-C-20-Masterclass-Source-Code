#include <print>
#include <stdexcept>
#include <vector>

void print_readings(const std::vector<int>& readings) {
    for (const int& reading : readings) {
        std::print("{} ", reading);
    }
    std::println("");
}

int main() {

    // std::vector<T> - like std::array, but its size can change at run
    // time and its elements live on the heap. vector(7) makes 7 elements,
    // each value-initialized to 0.
    std::vector<int> morning_readings(7);
    std::vector<int> evening_readings(10);

    std::println("Size of morning_readings is {}", morning_readings.size());
    print_readings(morning_readings);

    std::println("Size of evening_readings is {}", evening_readings.size());
    print_readings(evening_readings);

    // Two vectors compare element by element, like std::array.
    if (morning_readings != evening_readings) {
        std::println("morning_readings and evening_readings are not equal "
                      "(different sizes)");
    }

    // Copy constructor: afternoon_readings starts as an independent copy.
    std::vector afternoon_readings{morning_readings};
    std::println("\nSize of afternoon_readings is {}", afternoon_readings.size());

    // Assignment replaces morning_readings' contents with evening_readings'.
    morning_readings = evening_readings;
    std::println("\nAfter assigning evening_readings to morning_readings:");
    std::println("morning_readings and evening_readings are equal: {}",
                  morning_readings == evening_readings);

    // .at(i) as an lvalue: bounds-checked write.
    morning_readings.at(5) = 1000;
    std::print("morning_readings: ");
    print_readings(morning_readings);

    // Out-of-range access throws std::out_of_range - catch it instead of
    // crashing.
    try {
        std::println("\nAttempting morning_readings.at(15)");
        std::println("{}", morning_readings.at(15));
    }
    catch (const std::out_of_range& ex) {
        std::println("An exception occurred: {}", ex.what());
    }

    // A vector can grow. push_back appends one element, resizing as
    // needed - this is what std::array cannot do.
    std::println("\nCurrent afternoon_readings size is {}", afternoon_readings.size());
    afternoon_readings.push_back(1000);
    std::println("New afternoon_readings size is {}", afternoon_readings.size());
    std::print("afternoon_readings now contains: ");
    print_readings(afternoon_readings);

    return 0;
}
