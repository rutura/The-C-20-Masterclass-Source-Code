#include <iostream>
#include <print>

int main() {

    std::print("Enter a numeric grade (0-100): ");
    int grade{};
    std::cin >> grade;

    // --- Plain if: do something only when the condition holds ---
    if (grade == 100) {
        std::println("Perfect score!");
    }

    // --- if / else: one branch or the other ---
    if (grade >= 60) {
        std::println("Result: pass");
    }
    else {
        std::println("Result: fail");
    }

    // --- else if ladder: the first matching branch wins, the rest are
    // skipped. Order matters - check from the top down. ---
    if (grade >= 90) {
        std::println("Letter: A");
    }
    else if (grade >= 80) {
        std::println("Letter: B");
    }
    else if (grade >= 70) {
        std::println("Letter: C");
    }
    else if (grade >= 60) {
        std::println("Letter: D");
    }
    else {
        std::println("Letter: F");
    }

    // --- Nested if: a decision inside a branch ---
    if (grade >= 60) {
        if (grade >= 90) {
            std::println("Passed, and eligible for the honor roll.");
        }
        else {
            std::println("Passed.");
        }
    }

    // A variable declared inside a branch's { } exists only there.
    if (grade >= 60) {
        int margin{grade - 60};
        std::println("You cleared the pass mark by {} points.", margin);
    }
    // `margin` is not in scope here.

    return 0;
}
