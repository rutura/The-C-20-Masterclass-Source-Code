#include <iostream>
#include <print>
#include "in_range.h"

// A FUNCTION TEMPLATE is a pattern with the type left blank. `T` is a
// placeholder the compiler fills in from the arguments at each call,
// stamping out a concrete function on demand. One template stands in for
// a whole family of overloaded functions you would otherwise write by
// hand.


int main(){
    // The compiler deduces T from the argument types, then generates
    // that one version (in_range<int>, in_range<double>, ...).
    std::println("in_range(5, 1, 10)        : {}", in_range<double>(5, 1, 10.0));         // T = int
    // std::println("in_range(2.5, 0.0, 1.0)   : {}", in_range(2.5, 0.0, 1.0));    // T = double
    // std::println("in_range('g', 'a', 'm')   : {}", in_range('g', 'a', 'm'));    // T = char
}

