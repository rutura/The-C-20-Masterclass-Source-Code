#include <iostream>
#include <print>

int main() {

    std::print("Enter two student scores to compare: ");
    int score1{};
    int score2{};
    std::cin >> score1 >> score2;

    // Every one of these operators produces a bool: true or false.
    // std::println prints a bool as "true" / "false".
    std::println("score1 == score2 : {}", score1 == score2);   // equal
    std::println("score1 != score2 : {}", score1 != score2);   // not equal
    std::println("score1 <  score2 : {}", score1 < score2);
    std::println("score1 >  score2 : {}", score1 > score2);
    std::println("score1 <= score2 : {}", score1 <= score2);
    std::println("score1 >= score2 : {}", score1 >= score2);

    // The result is an ordinary value - you can name it and reuse it.
    bool first_is_better{score1 > score2};
    std::println("first student did better: {}", first_is_better);

    // A classic slip: = assigns, == compares. `score1 = score2` here
    // would overwrite score1 and evaluate to the assigned value, not a
    // comparison. Reach for == whenever you mean "are these equal?".

    return 0;
}
