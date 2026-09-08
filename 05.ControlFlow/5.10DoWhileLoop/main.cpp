#include <iostream>
#include <print>

int main() {

    // do...while runs the body FIRST, then tests the condition. So the
    // body always executes at least once - even if the condition is
    // false from the start. That's the whole reason to pick it over
    // while: when "do it, then decide whether to repeat" fits better
    // than "check, then maybe do it".

    // --- Prompt: ask at least once, repeat until the guess is valid ---
    int guess{};
    do {
        std::print("Guess the die roll (1-6): ");
        std::cin >> guess;

        if (guess < 1 || guess > 6) {
            std::println("  A die only shows 1-6, try again.");
        }
    } while (guess < 1 || guess > 6);

    std::println("You guessed: {}", guess);

    // --- Same counting job as a for loop, in do...while form ---
    int roll{1};
    do {
        std::print("{} ", roll);
        ++roll;
    } while (roll <= 10);
    std::println("");

    return 0;
}
