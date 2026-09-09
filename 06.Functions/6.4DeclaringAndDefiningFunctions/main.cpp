#include <iostream>
#include <print>

// A FUNCTION DECLARATION (also called a PROTOTYPE) tells the compiler a
// function's name, its parameter types, and its return type - everything
// a caller needs - before the function itself is defined. It ends with a
// semicolon and has no body.
//
// Declaration first, definition after main: main stays at the top where
// a reader looks first, and the compiler still knows how to check calls.
//
// The SIGNATURE is the name plus the parameter types. The return type is
// NOT part of it - so `double average(double,double,double)` and a
// hypothetical `int average(double,double,double)` would clash, not
// coexist. Parameter names in a declaration are optional; only the types
// matter: `double average(double, double, double);` is also valid.
double average(double a, double b, double c);   // declaration / prototype

int main() {

    std::print("Enter three numbers: ");
    double x{};
    double y{};
    double z{};
    std::cin >> x >> y >> z;

    // The compiler checks this call against the declaration above.
    std::println("average is {}", average(x, y, z));

    // ARGUMENT COERCION: an argument whose type differs from the
    // parameter type is converted, when a safe conversion exists. Here
    // 4, 8 and 15 are ints; the parameters are double, so each int is
    // widened to a double (4 -> 4.0) before the call.
    std::println("average of 4, 8, 15 is {}", average(4, 8, 15));

    // ORDER OF ARGUMENT EVALUATION IS UNSPECIFIED: the compiler may
    // evaluate a call's arguments in any order. If one argument's side
    // effect is observed by another, the result is not portable. Don't
    // write average(n++, n, n) and expect a particular reading of n.

    return 0;
}

// FUNCTION DEFINITION: the declaration's signature plus the { body }.
// Its first line must agree with the declaration (return type and
// parameter types).
double average(double a, double b, double c) {
    return (a + b + c) / 3.0;
}
