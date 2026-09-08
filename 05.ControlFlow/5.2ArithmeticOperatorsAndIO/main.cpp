#include <iostream>
#include <print>

int main() {

    // Two raw grades for one student, read from the keyboard.
    std::print("Enter two test scores (0-100), separated by a space: ");
    int score1{};
    int score2{};
    std::cin >> score1 >> score2;

    // --- The arithmetic operators ---
    std::println("sum        : {}", score1 + score2);
    std::println("difference : {}", score1 - score2);
    std::println("product    : {}", score1 * score2);

    // Integer / integer throws away the fractional part - 2 test scores
    // averaging to 74.5 come back as 74 here, not 74.5.
    std::println("average (int division)   : {}", (score1 + score2) / 2);

    // Make one operand a double and the division keeps the fraction.
    std::println("average (real division)  : {}", (score1 + score2) / 2.0);

    // Modulus gives the remainder - handy for "is this even?" or
    // "every Nth iteration" checks later in the chapter.
    std::println("score1 % 2 (0 means even): {}", score1 % 2);

    // --- Precedence and associativity ---
    // * binds tighter than +, so this is score1 + (score2 * 2), giving a
    // weighted total where the second test counts double.
    int weighted_total{score1 + score2 * 2};
    std::println("weighted total (score2 counts double): {}", weighted_total);

    // Parentheses override precedence when you want the addition first.
    int scaled{(score1 + score2) * 2};
    std::println("(score1 + score2) * 2: {}", scaled);

    // --- Compound assignment ---
    // running_total += x is shorthand for running_total = running_total + x.
    int running_total{score1};
    running_total += score2;   // add the second score
    running_total -= 5;        // late-submission penalty
    running_total *= 1;        // no-op, shown for completeness
    std::println("running total after += , -= : {}", running_total);

    return 0;
}
