#include <print>

int main() {

    // auto asks the compiler to work out a variable's type from its
    // initializer, instead of us spelling the type out ourselves. Literal
    // suffixes (u, l, f, ...) still steer which type gets deduced.
    auto expenseCount{7};                  // int
    auto transactionId{1'000'000};         // int
    auto amountSpent{93.33f};              // float, thanks to the f suffix
    auto categoryCode{'F'};                // char
    auto lifetimeCentsProcessed{9'000'000'000ll}; // long long, thanks to the ll suffix

    std::println("expenseCount             occupies {} bytes", sizeof(expenseCount));
    std::println("transactionId            occupies {} bytes", sizeof(transactionId));
    std::println("amountSpent              occupies {} bytes", sizeof(amountSpent));
    std::println("categoryCode             occupies {} bytes", sizeof(categoryCode));
    std::println("lifetimeCentsProcessed   occupies {} bytes", sizeof(lifetimeCentsProcessed));

    // The {...} braces above are *initializing* the variable - giving it its
    // very first value, at the moment it's created. A separate "=" without
    // braces later on is an *assignment* - replacing a value the variable
    // already has.
    std::println("");
    std::println("transactionId before assignment: {}", transactionId);
    transactionId = 1'250'000; // assignment: transactionId already existed
    std::println("transactionId after assignment : {}", transactionId);

    // Braced initialization refuses to silently throw away information -
    // this is called a narrowing conversion, and it won't compile:
    // int narrowed{93.33}; // compiler error: double doesn't fit losslessly in int

    // Plain assignment offers no such protection, which is exactly why we
    // reach for braces `{}` when declaring variables throughout this course -
    // and exactly the mistake that quietly loses cents in a real ledger.
    int narrowedAmount = 93.33; // compiles, but silently truncates to 93
    std::println("narrowedAmount (truncated): {}", narrowedAmount);

    // auto deduces a type once, at initialization - it doesn't update if you
    // later assign something that would have deduced differently. Assigning a
    // negative number into an auto that deduced unsigned wraps around instead
    // of going negative, same as we saw with unsigned int earlier.
    auto receiptsOnFile{250u}; // deduced: unsigned int
    receiptsOnFile = -10;      // DANGER: no negative unsigned values, this wraps around
    std::println("");
    std::println("receiptsOnFile after -10: {}", receiptsOnFile);

    return 0;
}
