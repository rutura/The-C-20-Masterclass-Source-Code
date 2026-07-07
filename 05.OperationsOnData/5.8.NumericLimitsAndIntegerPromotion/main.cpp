#include <print>
#include <limits>

int main() {

    // --- Numeric limits ---
    // Before trusting a type to hold an expense-tracker value, it helps to
    // know exactly how far that type can stretch. std::numeric_limits asks
    // the compiler directly, instead of us guessing or hardcoding numbers
    // that might not match this platform.
    std::println("short range         : {} to {}",
                  std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
    std::println("unsigned short range: {} to {}",
                  std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max());
    std::println("int range           : {} to {}",
                  std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::println("unsigned int range  : {} to {}",
                  std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max());
    std::println("long long range     : {} to {}",
                  std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max());

    // For floating-point types, ::min() is the smallest *positive* value
    // representable - not the most negative. ::lowest() is what gives the
    // true bottom of the range.
    std::println("");
    std::println("float lowest to max      : {} to {}",
                  std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
    std::println("double lowest to max     : {} to {}",
                  std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());

    // A few other useful facilities - full list at
    // https://en.cppreference.com/w/cpp/types/numeric_limits
    std::println("");
    std::println("int is_signed : {}", std::numeric_limits<int>::is_signed);
    std::println("int digits    : {}", std::numeric_limits<int>::digits);

    // --- Integer promotion ---
    // Knowing a type's declared size is only half the story - C++ also
    // promotes small integer types to a bigger one the moment you do
    // arithmetic on them, which is worth seeing directly rather than
    // assuming the result stays the same size as the operands.
    std::println("");
    short expenseCountA{10};
    short expenseCountB{20};

    char categoryCodeA{40};
    char categoryCodeB{50};

    std::println("sizeof(expenseCountA) : {}", sizeof(expenseCountA)); // 2
    std::println("sizeof(expenseCountB) : {}", sizeof(expenseCountB)); // 2
    std::println("sizeof(categoryCodeA) : {}", sizeof(categoryCodeA)); // 1
    std::println("sizeof(categoryCodeB) : {}", sizeof(categoryCodeB)); // 1

    // short + short, and char + char, both promote to int before the
    // addition happens - auto deduces int here, not short or char, even
    // though both operands were smaller.
    auto totalFromShorts = expenseCountA + expenseCountB;
    auto totalFromChars = categoryCodeA + categoryCodeB;

    std::println("sizeof(totalFromShorts): {}", sizeof(totalFromShorts)); // 4
    std::println("sizeof(totalFromChars) : {}", sizeof(totalFromChars));  // 4

    return 0;
}
