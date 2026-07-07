#include <print>

// Marking a function constexpr gives it the *potential* to run at compile
// time - but only when every argument it receives is itself known at
// compile time, and the result is stored in a constexpr variable. Called
// with a runtime value instead, it quietly falls back to running normally,
// at runtime.
constexpr double applyDiscount(double amount, double discountRate) {
    return amount * (1.0 - discountRate);
}

// consteval goes further: it forces the function to always run at compile
// time. Call it with a value the compiler can't know in advance, and it's a
// compiler error instead of a silent fallback to runtime.
consteval double applyFixedDiscount(double amount) {
    return amount * 0.90; // a fixed, always-known 10% discount
}

int main() {

    // Every input here is a literal, known at compile time, and the result
    // is stored in a constexpr variable - this is evaluated at compile time.
    constexpr double discounted = applyDiscount(100.0, 0.10);
    std::println("discounted : {}", discounted);

    // Called with a runtime variable instead, applyDiscount still works -
    // it just runs at runtime like an ordinary function would.
    double amountSpent{93.33};
    double runtimeDiscounted = applyDiscount(amountSpent, 0.10);
    std::println("runtimeDiscounted : {}", runtimeDiscounted);

    // applyFixedDiscount, being consteval, must be given a compile-time
    // known argument - this works because 100.0 is a literal.
    constexpr double fixedDiscounted = applyFixedDiscount(100.0);
    std::println("fixedDiscounted : {}", fixedDiscounted);

    // double result = applyFixedDiscount(amountSpent); // compiler error:
    // amountSpent isn't known until runtime, and consteval refuses that.

    return 0;
}
