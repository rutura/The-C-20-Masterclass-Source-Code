#include <print>

// A function that takes a parameter but gives nothing back (void) - it just
// does something and returns.
void printReceiptHeader(int transactionId) {
    std::println("--- Receipt #{} ---", transactionId);
}

// A function that takes multiple parameters and returns a computed result.
double applyDiscount(double amount, double discountRate) {
    return amount * (1.0 - discountRate);
}

// A function that takes no parameters and returns nothing - just a named,
// reusable action.
void printFooter() {
    std::println("--- Thank you! ---");
}

// A function that takes no parameters but still returns something.
double defaultTaxRate() {
    return 0.08;
}

int main() {

    printReceiptHeader(1001);

    double amountSpent{93.33};
    // Parameters are local copies - amountSpent itself is untouched by
    // whatever applyDiscount does with its own copy of it.
    double discounted = applyDiscount(amountSpent, 0.10);

    std::println("amountSpent (original) : {}", amountSpent);
    std::println("discounted             : {}", discounted);
    std::println("defaultTaxRate()       : {}", defaultTaxRate());

    printFooter();

    return 0;
}
