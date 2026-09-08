#include <print>

int main() {

    // Both ++ and -- change the variable by 1. The catch is what the
    // expression itself evaluates to when you use it inside a larger
    // statement.

    // --- Postfix: use the old value, THEN change ---
    int cars_owned{5};
    std::println("cars owned before buying one : {}", cars_owned);
    std::println("value of cars_owned++        : {}", cars_owned++);   // yields 5
    std::println("cars owned after buying one  : {}", cars_owned);     // now 6

    // --- Prefix: change FIRST, then use the new value ---
    cars_owned = 5;
    std::println("cars owned before buying one : {}", cars_owned);
    std::println("value of ++cars_owned        : {}", ++cars_owned);   // yields 6
    std::println("cars owned after buying one  : {}", cars_owned);     // still 6

    // As a standalone statement the two are interchangeable - this is by
    // far the most common way you'll use them, e.g. stepping a loop
    // counter later in this chapter.
    int cars_in_garage{3};
    --cars_in_garage;   // one just got sold
    std::println("cars in garage after selling one : {}", cars_in_garage);

    return 0;
}
