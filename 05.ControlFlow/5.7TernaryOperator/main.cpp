#include <iostream>
#include <print>
#include <string>

int main() {

    std::print("Enter a numeric grade (0-100): ");
    int grade{};
    std::cin >> grade;

    // The conditional operator: condition ? value_if_true : value_if_false
    // Unlike an if statement, this whole thing IS a value - so it can go
    // straight into an initializer or a print.
    std::string result{grade >= 60 ? "pass" : "fail"};
    std::println("Result: {}", result);

    // Written the long way, that's:
    std::string result_long{};
    if (grade >= 60) {
        result_long = "pass";
    }
    else {
        result_long = "fail";
    }
    std::println("Result (if/else version): {}", result_long);

    // Handy inline inside a larger message. Keep it to simple either/or
    // choices - chained ?: nested inside ?: gets unreadable fast, and an
    // else-if ladder is clearer there.
    std::println("You {} the class.", grade >= 60 ? "passed" : "did not pass");

    // Both branches must produce the same type. Here both are ints.
    int bonus{grade == 100 ? 5 : 0};
    std::println("Bonus points: {}", bonus);

    return 0;
}
