#include <print>

import stations;

int main() {
    Station north{make_station("north", {18.5, 24.0, 21.5})};
    Station silent{make_station("silent", {})};

    std::println("{}: mean {:.2f}, largest {}", north.name, mean_of(north), largest_of(north));
    std::println("{} is empty: {}   {} is empty: {}", north.name, is_empty(north), silent.name, is_empty(silent));

    // The exported template works for any type, because its body came with the interface.
    std::println("clamped(35, 0, 30)       = {}", clamped(35, 0, 30));
    std::println("clamped(-4.5, 0.0, 30.0) = {}", clamped(-4.5, 0.0, 30.0));

    // Importing a module gives you ITS exported names. It does not give you the
    // names of the headers the module included: include what you use yourself.
    // The vector inside Station can be used (its type is "reachable"), but
    // has_readings() cannot be called, because the module did not export it.
    north.readings.push_back(30.0);
    std::println("after push_back: {} readings", north.readings.size());
    return 0;
}
