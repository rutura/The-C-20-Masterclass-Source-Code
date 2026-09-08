#include <print>

// Two things about how a call gets set up.

// 1. ARGUMENT COERCION: an argument whose type differs from the
//    parameter type is converted to the parameter type, when a safe
//    conversion exists.
double square(double value) {
    return value * value;
}

// 2. The SIGNATURE is the name + parameter types. The return type is
//    NOT part of it. `int f(int)` and `double f(int)` have the same
//    signature and cannot coexist (more in the overloading lecture).

int main() {

    // 4 is an int; the parameter is double. The int is coerced to 4.0.
    std::println("square(4)    = {}", square(4));
    std::println("square(2.5)  = {}", square(2.5));

    // --- Order of argument evaluation is UNSPECIFIED ---
    // The compiler may evaluate a call's arguments in any order. If one
    // argument has a side effect that another depends on, the result is
    // not portable. Don't write code like this:
    int n{5};
    // std::println("{} {}", n++, n);   // which reads n first? unspecified.

    // Keep arguments free of side effects that other arguments observe:
    int a{n++};      // do the ++ in its own statement
    std::println("a = {}, n = {}", a, n);

    return 0;
}
