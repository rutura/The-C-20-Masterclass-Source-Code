#include <print>
#include <string>

// A function template is a pattern. `T` is a placeholder for a type
// the compiler fills in based on the arguments at each call. One
// template generates a whole family of concrete functions on demand.

template <typename T>
T maximum(T a, T b, T c) {
    T largest{a};
    if (b > largest) { largest = b; }
    if (c > largest) { largest = c; }
    return largest;
}

int main() {

    // The compiler deduces T from the argument types.
    std::println("max ints    : {}", maximum(3, 9, 5));          // T = int
    std::println("max doubles : {}", maximum(2.5, 1.1, 3.8));    // T = double
    std::println("max chars   : {}", maximum('q', 'a', 'm'));    // T = char

    std::string x{"apple"};
    std::string y{"pear"};
    std::string z{"fig"};
    std::println("max strings : {}", maximum(x, y, z));          // T = std::string

    // You can also state T explicitly. Here it forces the ints to be
    // treated as doubles.
    std::println("explicit    : {}", maximum<double>(3, 9, 5));

    return 0;
}
