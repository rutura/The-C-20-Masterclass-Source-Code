#include <print>

int main() {

    // --- Implicit conversions ---
    // When an expression mixes types, C++ converts one operand so both sides
    // match before computing anything - always from the smaller/less precise
    // type toward the bigger/more precise one. Adding an int amount of items
    // to a double price converts the int to double first, not the other way.
    double pricePerItem{45.6};
    int itemsBought{10};

    auto totalPrice = pricePerItem * itemsBought; // itemsBought promoted to double
    std::println("totalPrice           : {}", totalPrice);
    std::println("sizeof(totalPrice)   : {}", sizeof(totalPrice));

    // Assignment converts the other way around: the right-hand side is
    // converted to match the variable being assigned into, even if that
    // throws away information. This is a narrowing conversion happening
    // silently - the exact danger braced initialization protects against
    // for new variables (4.7), but assignment offers no such protection.
    int roundedTotal;
    roundedTotal = totalPrice; // double truncated to int, fractional cents lost
    std::println("roundedTotal         : {}", roundedTotal);

    // --- Explicit conversions ---
    // static_cast<T>(...) asks for a conversion on purpose, right where it
    // happens, instead of leaving the reader to notice an implicit one.
    double itemA{12.5};
    double itemB{34.6};

    // Cast first, then add: each item's cents are dropped before summing.
    int castThenSum = static_cast<int>(itemA) + static_cast<int>(itemB);
    std::println("");
    std::println("castThenSum          : {}", castThenSum); // 12 + 34 = 46

    // Add first, then cast: same result as the implicit conversion above,
    // but the truncation is explicit instead of hidden in an assignment.
    int sumThenCast = static_cast<int>(itemA + itemB);
    std::println("sumThenCast          : {}", sumThenCast); // 47

    // static_cast is the modern replacement for the old C-style cast
    // ((int)itemA) - it does the same job here, but the compiler also
    // checks that the conversion makes sense, and a reader can search for
    // "static_cast" instead of hunting for stray parentheses.
    int oldStyleCast = (int)itemA;         // works, but not preferred in C++
    int modernCast = static_cast<int>(itemA);
    std::println("oldStyleCast         : {}", oldStyleCast);
    std::println("modernCast           : {}", modernCast);

    return 0;
}
