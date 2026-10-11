#include <print>
#include <string>
#include <vector>

import units;
import limits;
import statistics;
import clamp;
import weather;
import alarms;

int main() {

    std::println("--- Exercise 1: a first module ---");
    std::println("21.5 C = {} F = {} K", to_fahrenheit(21.5), to_kelvin(21.5));

    std::println("\n--- Exercise 2: a struct and a constant ---");
    std::println("comfortable range: {} to {}", comfortable.low, comfortable.high);
    std::println("22 is comfortable: {}   30 is comfortable: {}", within(comfortable, 22.0), within(comfortable, 30.0));

    std::println("\n--- Exercise 3: interface and implementation ---");
    std::vector<double> temperatures{18.5, 24.0, 21.5, 12.0};
    std::println("mean {:.2f}, largest {}", mean_of(temperatures), largest_of(temperatures));

    std::println("\n--- Exercise 4: a template in a module ---");
    std::println("clamped(35, 0, 30) = {}   clamped(-4.5, 0.0, 30.0) = {}", clamped(35, 0, 30), clamped(-4.5, 0.0, 30.0));

    std::println("\n--- Exercise 5: partitions ---");
    for (const Reading& reading : {Reading{6, 11.5}, Reading{12, 26.0}, Reading{18, 19.0}}) {
        std::println("{}", describe(reading));
    }

    std::println("\n--- Exercise 7: wrapping a legacy header ---");
    Alarm alarm{make_alarm(2, "battery low")};
    std::println("{}: {} (levels go up to {})", describe_level(alarm.level), alarm.text, alarm_levels);
    return 0;
}
