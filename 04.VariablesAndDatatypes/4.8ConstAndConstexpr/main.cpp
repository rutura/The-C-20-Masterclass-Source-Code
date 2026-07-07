#include <print>

int main() {

    // Some values in an expense tracker should never change once set - a tax
    // rate for the year, the number of categories the program supports. const
    // says "this variable can be initialized once, then never reassigned" -
    // the compiler enforces it for us.
    const double taxRate{0.08};
    const int categoryCount{4}; // Food, Transport, Entertainment, Other

    std::println("taxRate       : {}", taxRate);
    std::println("categoryCount : {}", categoryCount);

    // taxRate = 0.10; // compiler error: can't reassign a const variable

    // A regular variable can still be used to compute a const one - the
    // *result* is locked in, even though one of its ingredients wasn't const.
    double amountSpent{93.33};
    const double amountWithTax{amountSpent * (1.0 + taxRate)};
    std::println("amountWithTax : {:.2f}", amountWithTax);

    // constexpr goes a step further than const: it tells the compiler this
    // value must be computable at *compile time*, before the program even
    // runs - not just "never reassigned", but "known before main() starts".
    // That's stronger than most everyday values need (amountSpent isn't known
    // until someone types it in), but it's exactly right for a fixed limit
    // like a receipt threshold that gets checked on every expense.
    constexpr double receiptRequiredAbove{25.0};
    std::println("receiptRequiredAbove : {}", receiptRequiredAbove);

    // A constexpr variable can only be initialized from things the compiler
    // can already work out on its own - other constexpr values, or literals.
    constexpr int maxCategoriesSupported{8};
    constexpr int categoryBitsNeeded{3}; // enough bits to count up to 8 categories

    // This would fail: amountSpent is only known once the program is running,
    // so the compiler can't fold it into a constexpr.
    // constexpr double badExample{amountSpent}; // compiler error

    // But a constexpr can be built from another constexpr just fine - the
    // compiler works out the whole chain during compilation.
    constexpr int maxCategoriesDoubled{maxCategoriesSupported * 2};
    std::println("maxCategoriesDoubled : {}", maxCategoriesDoubled);

    std::println("categoryBitsNeeded   : {}", categoryBitsNeeded);

    return 0;
}
