#include <print>

int main() {

    // --- Increment and decrement ---
    // Bumping a running expense count up or down by exactly one is common
    // enough that C++ gives it its own shorthand: ++ and --.
    int expenseCount{5};

    expenseCount = expenseCount + 1; // the long way to add one
    std::println("expenseCount after +1        : {}", expenseCount); // 6

    expenseCount = 5; // reset
    expenseCount = expenseCount - 1;
    std::println("expenseCount after -1        : {}", expenseCount); // 4

    // Postfix (value++): evaluates to the value *before* incrementing, then
    // increments. Useful when you need "the id we just used", not the next one.
    expenseCount = 5;
    std::println("expenseCount++ (postfix) gave: {}", expenseCount++); // 5
    std::println("expenseCount is now          : {}", expenseCount);  // 6

    // Prefix (++value): increments first, then evaluates to the new value.
    expenseCount = 5;
    std::println("++expenseCount (prefix) gave : {}", ++expenseCount); // 6

    // --- Compound assignment ---
    // "Take this variable, apply an operation, store the result back into
    // itself" is common enough to deserve its own shorthand too - one
    // operator instead of writing the variable's name twice.
    int monthlyBudget{200};
    std::println("");
    std::println("monthlyBudget                 : {}", monthlyBudget);

    monthlyBudget += 50; // equivalent to: monthlyBudget = monthlyBudget + 50
    std::println("monthlyBudget after += 50      : {}", monthlyBudget); // 250

    monthlyBudget -= 30;
    std::println("monthlyBudget after -= 30      : {}", monthlyBudget); // 220

    monthlyBudget *= 2; // e.g. planning for a two-month trip
    std::println("monthlyBudget after *= 2       : {}", monthlyBudget); // 440

    monthlyBudget /= 4; // split across a 4-person shared account
    std::println("monthlyBudget after /= 4       : {}", monthlyBudget); // 110

    monthlyBudget %= 30; // whatever doesn't divide evenly into a 30-day month
    std::println("monthlyBudget after %= 30      : {}", monthlyBudget); // 20

    return 0;
}
