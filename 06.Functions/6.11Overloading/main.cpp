#include <print>

// Overloading: several functions can share a name as long as their
// parameter lists differ (in number or types). The compiler picks the
// one that matches the arguments at each call site. The return type
// alone is NOT enough to tell overloads apart.

int square(int x) {
    std::println("  (int version)");
    return x * x;
}

double square(double x) {
    std::println("  (double version)");
    return x * x;
}

// Different number of parameters is also an overload.
int area(int side) {
    return side * side;
}

int area(int width, int height) {
    return width * height;
}

int main() {

    std::println("square(7)   = {}", square(7));      // exact match -> int
    std::println("square(7.5) = {}", square(7.5));    // exact match -> double
    std::println("square(7.0f) = {}", square(7.0f));  // float promotes -> double

    std::println("area(5)     = {}", area(5));        // one arg  -> side*side
    std::println("area(4, 6)  = {}", area(4, 6));     // two args -> w*h

    return 0;
}
