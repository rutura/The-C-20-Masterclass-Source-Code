#include <print>

// OVERLOADING: several functions can share one name as long as their
// PARAMETER LISTS differ (in number or type). At each call the compiler
// picks the best match. The return type alone cannot distinguish
// overloads.

int square(int x) {
    std::print("(int) ");
    return x * x;
}

double square(double x) {
    std::print("(double) ");
    return x * x;
}

int main() {

    std::println("square(7)   = {}", square(7));      // exact match -> int version
    std::println("square(7.5) = {}", square(7.5));    // exact match -> double version

    // Behind the scenes the compiler gives each overload a distinct
    // internal name based on its parameter types ("name mangling"), so
    // the two `square`s never collide at link time.

    return 0;
}
