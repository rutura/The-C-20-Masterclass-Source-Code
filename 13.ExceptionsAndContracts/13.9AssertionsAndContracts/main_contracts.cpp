#include <print>

// C++26 contracts: the same idea as assert, but part of the function's
// DECLARATION, so callers can see the rules, and tools can use them.
//
//   pre(...)            what the caller must guarantee
//   post(r : ...)       what the function guarantees back (r names the result)
//   contract_assert(..) a check in the middle of the body
//
// A parameter named in a post condition must be const.
double battery_percent(const double volts)
    pre(volts >= 0.0)
    post(r : r >= 0.0 && r <= 100.0)
{
    const double raw{(volts - 3.0) / 1.2 * 100.0};
    const double result{raw < 0.0 ? 0.0 : (raw > 100.0 ? 100.0 : raw)};
    contract_assert(result == result);              // a NaN is never equal to itself
    return result;
}

int main(int argc, char**) {

    for (double volts : {2.5, 3.6, 4.2, 5.0}) {
        std::println("{:.1f} V -> {:.0f} %", volts, battery_percent(volts));
    }

    if (argc > 1) {
        std::println("\ncalling with a negative voltage...");
        std::println("{}", battery_percent(-1.0));    // breaks the precondition
    }
    return 0;
}
