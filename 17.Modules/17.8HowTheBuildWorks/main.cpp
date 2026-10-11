#include <print>

import readings;
import report;

int main() {
    Reading day[]{{6, 11.5}, {12, 24.0}, {18, 15.0}};

    std::println("warmest hour: {}", hour_of_warmest(day, 3));
    std::println("at that hour: {} F", day[1].fahrenheit());
    return 0;
}
