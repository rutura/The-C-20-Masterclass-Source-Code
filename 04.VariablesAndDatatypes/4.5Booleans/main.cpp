#include <print>

int main() {

    // A bool holds only one of two values, true or false - perfect for the
    // yes/no questions an expense tracker needs to answer.
    bool hasReceipt{false};
    bool isOverBudget{true};

    if (hasReceipt == true) {
        std::println("Receipt on file.");
    } else {
        std::println("No receipt - might get flagged in an audit.");
    }

    // Comparing a bool to true/false explicitly works, but it's redundant -
    // the bool itself already is the yes/no answer.
    if (isOverBudget) {
        std::println("Over budget this month!");
    } else {
        std::println("Still within budget.");
    }

    std::println("sizeof(bool): {}", sizeof(bool));

    // std::println formats bools as the words "true"/"false" by default,
    // which is what we want almost all the time.
    std::println("");
    std::println("hasReceipt   : {}", hasReceipt);
    std::println("isOverBudget : {}", isOverBudget);

    // {:d} instead formats a bool as the underlying integer instead:
    // 1 for true, 0 for false.
    std::println("hasReceipt   : {:d}", hasReceipt);
    std::println("isOverBudget : {:d}", isOverBudget);

    return 0;
}
