// #include "pricing.h" brings in the declarations only - the compiler just
// needs to know these functions exist and what they look like to check this
// file compiles correctly. Their actual definitions live in pricing.cpp,
// compiled separately and stitched together at link time.
#include <print>
#include "pricing.h"

int main() {

    double amountSpent{93.33};

    double discounted = applyDiscount(amountSpent, 0.10);
    double withTax = applyTax(discounted, 0.08);

    std::println("discounted : {}", discounted);
    std::println("withTax    : {}", withTax);

    return 0;
}
