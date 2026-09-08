#include <iostream>
#include <print>

int main() {

    // do...while runs the body FIRST, then tests the condition. So the
    // body always executes at least once - even if the condition is
    // false from the start. That's the whole reason to pick it over
    // while: when "do it, then decide whether to repeat" fits better
    // than "check, then maybe do it".

    // --- Menu-style prompt: ask at least once, repeat until valid ---
    int grade{};
    do {
        std::print("Enter a grade in the range 0-100: ");
        std::cin >> grade;

        if (grade < 0 || grade > 100) {
            std::println("  Out of range, try again.");
        }
    } while (grade < 0 || grade > 100);

    std::println("Accepted grade: {}", grade);

    // --- Same counting job as a for loop, in do...while form ---
    int counter{1};
    do {
        std::print("{} ", counter);
        ++counter;
    } while (counter <= 10);
    std::println("");

    return 0;
}
