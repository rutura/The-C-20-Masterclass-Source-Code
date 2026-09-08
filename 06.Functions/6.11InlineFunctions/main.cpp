#include <iostream>
#include <print>

// `inline` on a function definition permits that definition to appear in
// more than one translation unit (typically because it lives in a header
// included by several .cpp files) without a "multiple definition" linker
// error. All the definitions must be identical; the linker treats them
// as one.
//
// It is NOT a command to "paste the body at the call site" - the
// compiler already decides that on its own, inline keyword or not.
//
// A function defined before its first use (like this one) needs no
// separate prototype: the definition's first line serves as one.
inline double cube(double side) {
    return side * side * side;
}

int main() {

    std::print("Enter the side length of a cube: ");
    double side{};
    std::cin >> side;

    std::println("volume = {}", cube(side));

    return 0;
}
