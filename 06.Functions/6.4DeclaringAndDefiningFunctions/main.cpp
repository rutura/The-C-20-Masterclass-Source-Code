#include <iostream>
#include <print>

// A FUNCTION PROTOTYPE tells the compiler a function's name, its
// parameter types, and its return type - everything a caller needs -
// before the function itself is defined. It ends with a semicolon and
// has no body.
//
// Prototype first, definition after main: main stays at the top where a
// reader looks first, and the compiler still knows how to check the
// call.

double average(double a, double b, double c);   // prototype

int main() {

    std::print("Enter three numbers: ");
    double x{};
    double y{};
    double z{};
    std::cin >> x >> y >> z;

    // The compiler checks this call against the prototype above.
    std::println("average is {}", average(x, y, z));

    return 0;
}

// FUNCTION DEFINITION: the prototype's signature plus the { body }.
// Its first line must agree with the prototype.
double average(double a, double b, double c) {
    return (a + b + c) / 3.0;
}
