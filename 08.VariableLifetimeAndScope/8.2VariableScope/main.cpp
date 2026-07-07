#include <print>

// A variable declared outside any function has global scope - it's alive for
// the entire program, and every function below can see it. Handy for a
// setting the whole program agrees on, but easy to abuse: change taxRate
// from deep inside some unrelated function, and every other function using
// it is affected too, with no clue from the call site that it happened.
double taxRate{0.08};

void printReceiptFooter() {
    // No parameter needed to reach taxRate - it's visible everywhere.
    std::println("(tax rate applied: {})", taxRate);
}

int main() {

    // A variable declared inside main - or any block - has local scope. It
    // comes into existence when its declaration runs, and is destroyed the
    // moment its enclosing braces close. Nothing outside those braces can
    // see it.
    double amountSpent{93.33};
    std::println("amountSpent : {}", amountSpent);

    // if-statements and loops open their own block, with their own scope.
    // A variable declared inside one only lives as long as that block does -
    // it doesn't leak out into main(), and a fresh copy is created (and
    // destroyed) on every loop iteration.
    if (amountSpent > 50.0) {
        // discountApplied only exists between these braces.
        double discountApplied{amountSpent * 0.10};
        std::println("Over 50 - discount applied: {}", discountApplied);
    }
    // std::println("{}", discountApplied); // compiler error: out of scope here

    std::println("");
    for (int i{0}; i < 3; ++i) {
        // logEntry is created and destroyed fresh on every pass through the
        // loop - it never carries a value over from the previous iteration.
        int logEntry{i + 1};
        std::println("Logging expense entry #{}", logEntry);
    }
    // std::println("{}", logEntry); // compiler error: i and logEntry don't exist here

    printReceiptFooter();

    return 0;
}
