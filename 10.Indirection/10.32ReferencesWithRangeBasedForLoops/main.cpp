#include <print>

int main() {

    int scores[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::println("");
    std::print("Scores : ");
    for (auto score : scores) { // a copy - modifying score here wouldn't touch scores
        std::print(" {}", score);
    }
    std::println("");

    // auto& binds each element by reference, so modifying score here
    // modifies the array itself.
    for (auto& score : scores) {
        score = score * 10;
    }

    std::println("");
    std::print("Scores : ");
    for (auto score : scores) {
        std::print(" {}", score);
    }
    std::println("");

    return 0;
}
