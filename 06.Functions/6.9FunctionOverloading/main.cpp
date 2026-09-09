#include <print>

// OVERLOADING: several functions can share one name as long as their
// PARAMETER LISTS differ - in number, type, or order. At each call the
// compiler examines the arguments and picks the matching version.
//
// It is for one idea carried out on different inputs. Here: "area of a
// shape", where the shape is implied by what you pass.

// area of a square, from its side
int area(int side) {
    std::print("(square) ");
    return side * side;
}

// area of a circle, from its radius - different parameter TYPE
double area(double radius) {
    std::print("(circle) ");
    return 3.14159 * radius * radius;
}

// area of a rectangle - different parameter COUNT
int area(int width, int height) {
    std::print("(rectangle) ");
    return width * height;
}

int main() {

    std::println("area(4)     = {}", area(4));       // one int   -> square
    std::println("area(2.5)   = {}", area(2.5));     // one double -> circle
    std::println("area(3, 6)  = {}", area(3, 6));    // two ints  -> rectangle

    // The compiler tells the three apart by their SIGNATURE - the name
    // plus the parameter types in order. The return type is not part of
    // it, which is why `int area(int)` and `double area(int)` could not
    // coexist. Internally each overload gets a distinct mangled name
    // (area(int) -> _Z4areai under GNU C++), so they never clash at link
    // time; that encoding is compiler-specific.

    return 0;
}
