#include <print>

int main() {

    // A lambda is a small, unnamed function written right where it's used.
    // Its general shape: [capture list](parameters) -> return type { body }.
    // With no captures yet (the next chapter's lambda lecture covers those),
    // it behaves like a regular function you happen to be defining inline.

    // Declared once, given a name via auto, and called as many times as needed.
    auto applyDiscount = [](double amount, double discountRate) {
        return amount * (1.0 - discountRate);
    };

    double amountSpent{93.33};
    double discounted = applyDiscount(amountSpent, 0.10);
    std::println("discounted : {:.2f}", discounted);

    // Explicitly specifying the return type (-> double) instead of letting
    // it be deduced - occasionally needed when a lambda's return type would
    // otherwise be ambiguous.
    auto applyTax = [](double amount, double taxRate) -> double {
        return amount * (1.0 + taxRate);
    };
    std::println("withTax    : {:.2f}", applyTax(discounted, 0.08));

    // A lambda can also be declared and called immediately, without ever
    // being given a name - useful for a one-off computation.
    double doubled = [](double amount) {
        return amount * 2.0;
    }(amountSpent);
    std::println("doubled    : {:.2f}", doubled);

    return 0;
}
