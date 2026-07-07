#include <print>

int main() {

    // A bool holds only one of two values, true or false - perfect for the
    // yes/no questions an arcade tracker needs to answer.
    bool isGameOver{false};
    bool isNewHighScore{true};

    if (isGameOver == true) {
        std::println("Game over!");
    } else {
        std::println("Still playing...");
    }

    // Comparing a bool to true/false explicitly works, but it's redundant -
    // the bool itself already is the yes/no answer.
    if (isNewHighScore) {
        std::println("New high score!");
    } else {
        std::println("No record this time.");
    }

    std::println("sizeof(bool): {}", sizeof(bool));

    // std::println formats bools as the words "true"/"false" by default,
    // which is what we want almost all the time.
    std::println("");
    std::println("isGameOver     : {}", isGameOver);
    std::println("isNewHighScore : {}", isNewHighScore);

    // {:d} instead formats a bool as the underlying integer instead:
    // 1 for true, 0 for false.
    std::println("isGameOver     : {:d}", isGameOver);
    std::println("isNewHighScore : {:d}", isNewHighScore);

    return 0;
}
