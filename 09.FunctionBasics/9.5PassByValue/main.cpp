#include <print>

// Every parameter here is a fresh, local copy of whatever the caller passed
// in. Changing it inside the function has no effect on the caller's
// variable - the address of the parameter and the caller's variable are
// different, because they're different objects in memory.
double addLoyaltyBonus(double amount) {
    amount += 5.0; // only changes this function's local copy
    return amount;
}

// A const parameter is still a copy, but marking it const documents (and
// enforces) that this function has no intention of changing it - useful for
// a reader skimming the signature, and it catches an accidental mutation as
// a compiler error instead of a silent bug.
double previewWithTax(const double amount, const double taxRate) {
    // amount += 1.0; // compiler error: amount is const
    return amount * (1.0 + taxRate);
}

int main() {

    double amountSpent{93.33};

    double bonused = addLoyaltyBonus(amountSpent);
    std::println("amountSpent (unchanged) : {}", amountSpent);
    std::println("bonused                 : {}", bonused);

    double preview = previewWithTax(amountSpent, 0.08);
    std::println("preview (with tax)      : {}", preview);

    return 0;
}
