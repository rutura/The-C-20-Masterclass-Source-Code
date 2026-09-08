#include <print>

// A function is a named block of code you can run ("call") from
// elsewhere. It can take inputs (parameters) and hand back a result
// (a return value). Writing something once as a function and calling it
// many times is how programs stay manageable as they grow.

// --- A function that takes inputs and returns a result ---
// Parameters: x, y, z. Return type: int.
int maximum(int x, int y, int z) {
    int largest{x};             // assume x is the largest to start
    if (y > largest) {
        largest = y;
    }
    if (z > largest) {
        largest = z;
    }
    return largest;             // hand the result back to the caller
}

// --- A function that takes no inputs and returns nothing ---
// Return type void = "no value comes back".
void print_banner() {
    std::println("=== number tools ===");
    // no return statement needed for a void function
}

int main() {

    print_banner();             // call: run print_banner, then come back here

    int a{12};
    int b{47};
    int c{30};

    // A call is an expression that evaluates to the return value, so it
    // can be used anywhere a value is expected - here, as an argument.
    std::println("maximum of {}, {}, {} is {}", a, b, c, maximum(a, b, c));

    // Arguments don't have to be variables - literals work too.
    std::println("maximum of 3, 9, 5 is {}", maximum(3, 9, 5));

    // The result can be stored and reused.
    int biggest{maximum(a, b, c)};
    std::println("biggest, doubled: {}", biggest * 2);

    return 0;
}
