#include <print>

// This function expects two ints...
int addQuantities(int a, int b) {
    std::println("sizeof(a) : {}", sizeof(a));
    std::println("sizeof(b) : {}", sizeof(b));
    return a + b;
}

int main() {

    // ...but these arguments are doubles. C++ implicitly converts each one
    // to int before the call happens - narrowing the value and silently
    // dropping anything after the decimal point, the same danger seen with
    // narrowing assignments back in chapter 4.
    double itemsA{4.9};
    double itemsB{7.8};

    int total = addQuantities(itemsA, itemsB); // itemsA, itemsB narrowed to int
    std::println("total : {}", total); // 4 + 7 = 11, not 12.7

    return 0;
}
