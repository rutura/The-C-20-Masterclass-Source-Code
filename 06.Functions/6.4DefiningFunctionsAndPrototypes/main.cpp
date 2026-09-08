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

int maximum(int x, int y, int z);   // prototype

int main() {

    std::print("Enter three integers: ");
    int a{};
    int b{};
    int c{};
    std::cin >> a >> b >> c;

    // The compiler checks this call against the prototype above.
    std::println("maximum is {}", maximum(a, b, c));

    return 0;
}

// FUNCTION DEFINITION: the prototype's signature plus the { body }.
// Its first line must agree with the prototype.
int maximum(int x, int y, int z) {
    int largest{x};                 // assume x is the largest to start
    if (y > largest) {
        largest = y;
    }
    if (z > largest) {
        largest = z;
    }
    return largest;
}
