#include <iostream>
#include <print>

int main() {

    std::print("Enter your age in years: ");
    int age{};
    std::cin >> age;

    // --- Plain if: do something only when the condition holds ---
    if (age == 18) {
        std::println("Just became an adult!");
    }

    // --- if / else: one branch or the other ---
    if (age >= 18) {
        std::println("Status: adult");
    }
    else {
        std::println("Status: minor");
    }

    // --- else if ladder: the first matching branch wins, the rest are
    // skipped. Order matters - check from the top down. ---
    if (age >= 65) {
        std::println("Bracket: senior");
    }
    else if (age >= 18) {
        std::println("Bracket: adult");
    }
    else if (age >= 13) {
        std::println("Bracket: teenager");
    }
    else if (age >= 0) {
        std::println("Bracket: child");
    }
    else {
        std::println("Bracket: invalid age");
    }

    // --- Nested if: a decision inside a branch ---
    if (age >= 18) {
        if (age >= 21) {
            std::println("Adult, and old enough to enter the club.");
        }
        else {
            std::println("Adult, but under 21.");
        }
    }

    // A variable declared inside a branch's { } exists only there.
    if (age >= 18) {
        int years_since_adult{age - 18};
        std::println("You've been an adult for {} years.", years_since_adult);
    }
    // `years_since_adult` is not in scope here.

    return 0;
}
