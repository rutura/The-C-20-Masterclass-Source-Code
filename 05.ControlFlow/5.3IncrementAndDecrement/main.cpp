#include <print>

int main() {

    // Both ++ and -- change the variable by 1. The catch is what the
    // expression itself evaluates to when you use it inside a larger
    // statement.

    // --- Postfix: use the old value, THEN change ---
    int graded{5};
    std::println("graded before postincrement : {}", graded);
    std::println("value of graded++           : {}", graded++);   // yields 5
    std::println("graded after postincrement  : {}", graded);     // now 6

    // --- Prefix: change FIRST, then use the new value ---
    graded = 5;
    std::println("graded before preincrement  : {}", graded);
    std::println("value of ++graded           : {}", ++graded);   // yields 6
    std::println("graded after preincrement   : {}", graded);     // still 6

    // As a standalone statement the two are interchangeable - this is by
    // far the most common way you'll use them, e.g. stepping a loop
    // counter later in this chapter.
    int remaining{3};
    --remaining;
    std::println("remaining after --remaining : {}", remaining);

    return 0;
}
