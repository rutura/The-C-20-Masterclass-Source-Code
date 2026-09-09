#include <print>

// A FUNCTION TEMPLATE is a pattern with the type left blank. `T` is a
// placeholder the compiler fills in from the arguments at each call,
// generating a concrete function on demand. One template stands in for a
// whole family of overloaded functions you would otherwise write by hand.

template <typename T>
T maximum(T a, T b, T c) {
    T largest{a};
    if (b > largest) {
        largest = b;
    }
    if (c > largest) {
        largest = c;
    }
    return largest;
}

int main() {

    // The compiler deduces T from the argument types.
    std::println("max of ints    : {}", maximum(3, 9, 5));         // T = int
    std::println("max of doubles : {}", maximum(2.5, 1.1, 3.8));   // T = double
    std::println("max of chars   : {}", maximum('q', 'a', 'm'));   // T = char

    // All three arguments must agree on T. maximum(3, 9.0, 5) would fail
    // to deduce a single type - state it explicitly instead:
    std::println("forced double  : {}", maximum<double>(3, 9, 5));

    return 0;
}
