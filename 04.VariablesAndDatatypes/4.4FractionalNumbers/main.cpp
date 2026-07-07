#include <print>

int main() {

    // Not every expense-tracker number is a whole number - an amount spent
    // needs a fractional part (cents). C++ has three floating-point types for
    // that, each trading off size for precision.

    float amountSpent{93.3333333333333f};      // ~7 significant digits
    double averageDailySpend{0.185185185185};  // ~15-16 significant digits
    long double preciseAverage{93.3333333333333333L};

    std::println("sizeof(float)      : {}", sizeof(float));
    std::println("sizeof(double)     : {}", sizeof(double));
    std::println("sizeof(long double): {}", sizeof(long double));

    // {:.15f} asks std::println to print 15 digits after the decimal point,
    // which exposes each type's real precision limit.
    std::println("amountSpent        : {:.15f}", amountSpent);
    std::println("averageDailySpend  : {:.15f}", averageDailySpend);
    std::println("preciseAverage     : {:.15f}", preciseAverage);

    // float's limited precision is why it's a poor fit for a running total of
    // money - this "obviously wrong" digit drift is the classic symptom, and
    // exactly the kind of bug that quietly corrupts a ledger over time.
    float totalSpentThisYear = 1'924'000.23f; // looks fine printed normally...
    std::println("totalSpentThisYear : {:.5f}", totalSpentThisYear); // ...but isn't, at this precision

    // Scientific notation is handy once numbers get very large or very small -
    // like a large company's annual revenue, or the fraction of a cent a
    // currency-conversion fee might round to.
    std::println("");
    double roundingFeeFraction{3.498e-11};   // 3.498 * 10^-11
    double annualRevenue{1.924e8};           // 1.924 * 10^8
    std::println("roundingFeeFraction : {}", roundingFeeFraction);
    std::println("annualRevenue       : {}", annualRevenue);

    // Dividing by zero doesn't crash for floating-point types the way it does
    // for integers - it produces special values instead: infinity and NaN
    // ("not a number"). A classic place this shows up: computing an "average
    // expense" when there are zero expenses logged yet.
    std::println("");
    double totalSpent{-5.6};
    double expenseCount{};

    double infinityResult{totalSpent / expenseCount};
    std::println("{} / {} = {}", totalSpent, expenseCount, infinityResult);

    double zero{};
    double nanResult{zero / expenseCount};
    std::println("{} / {} = {}", zero, expenseCount, nanResult);

    return 0;
}
