#include <print>

// A default parameter value is used whenever the caller doesn't supply one.
// Once a parameter has a default, every parameter after it needs one too -
// the compiler fills arguments in from left to right, so it can't "skip"
// one in the middle.
void printReceipt(double amount, double taxRate = 0.08, bool showFooter = true) {
    double total = amount * (1.0 + taxRate);
    std::println("amount     : {}", amount);
    std::println("taxRate    : {}", taxRate);
    std::println("total      : {:.2f}", total);
    if (showFooter) {
        std::println("--- Thank you! ---");
    }
}

int main() {

    printReceipt(50.0);                  // taxRate and showFooter use their defaults
    std::println("");
    printReceipt(50.0, 0.05);            // taxRate overridden, showFooter still defaults
    std::println("");
    printReceipt(50.0, 0.05, false);     // every argument supplied explicitly

    return 0;
}
