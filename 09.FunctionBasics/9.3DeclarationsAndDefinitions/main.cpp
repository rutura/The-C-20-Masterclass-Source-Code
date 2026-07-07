#include <print>

// A function declaration (a "prototype") tells the compiler this function
// exists and what it looks like, without providing the body yet - that
// makes it possible to call the function from main() below, even though
// its definition doesn't appear until after main().
double applyDiscount(double amount, double discountRate);
double applyTax(double amount, double taxRate);

int main() {

    double amountSpent{93.33};

    double discounted = applyDiscount(amountSpent, 0.10);
    std::println("discounted : {}", discounted);

    double withTax = applyTax(discounted, 0.08);
    std::println("withTax    : {}", withTax);

    return 0;
}

// Function definitions - the actual bodies - can live below main(), or in a
// completely different file (the next lecture shows that).
double applyDiscount(double amount, double discountRate) {
    return amount * (1.0 - discountRate);
}

double applyTax(double amount, double taxRate) {
    return amount * (1.0 + taxRate);
}
