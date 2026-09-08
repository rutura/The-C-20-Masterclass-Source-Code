#include <print>

int main() {

    // C++17 lets you declare a variable right in the `if` or `switch`
    // header, before the condition, separated by a semicolon:
    //     if (init; condition) { ... }
    // The variable is in scope for the whole if/else (or switch), and
    // nowhere else - so it can't leak or collide with anything after.

    // --- if with initializer ---
    if (int grade{87}; grade >= 60) {
        std::println("grade {} is a pass", grade);
    }
    else {
        std::println("grade {} is a fail", grade);
    }
    // `grade` does not exist here.

    if (int grade{42}; grade >= 90) {
        std::println("grade {} earns an A", grade);
    }
    else {
        std::println("grade {} does not earn an A", grade);
    }

    // --- switch with initializer ---
    // Compute the bucket once in the header, then switch on it.
    switch (int score{73}; score / 10) {
        case 10:
        case 9:
            std::println("score {}: A", score);
            break;
        case 8:
            std::println("score {}: B", score);
            break;
        case 7:
            std::println("score {}: C", score);
            break;
        default:
            std::println("score {}: D or below", score);
            break;
    }

    // Use this whenever a value is needed only to make one decision -
    // it keeps that value's lifetime as short as the decision itself.

    return 0;
}
