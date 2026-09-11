#include <print>

#include "in_range.h"   // the template's BODY comes in here - the compiler
                        // needs to see it to stamp out each version

int main() {

    // The compiler deduces T from the argument types, then generates
    // that one version (in_range<int>, in_range<double>, ...).
    std::println("in_range(5, 1, 10)        : {}", in_range(5, 1, 10));         // T = int
    std::println("in_range(2.5, 0.0, 1.0)   : {}", in_range(2.5, 0.0, 1.0));    // T = double
    std::println("in_range('g', 'a', 'm')   : {}", in_range('g', 'a', 'm'));    // T = char

    // All three arguments must agree on T. in_range(5, 1, 10.0) mixes
    // int and double, so deduction fails - state the type instead:
    std::println("in_range<double>(5, 1, 10): {}", in_range<double>(5, 1, 10));

    return 0;
}
