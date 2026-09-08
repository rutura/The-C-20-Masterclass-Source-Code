#include <cmath>       // std::pow, std::fabs
#include <print>

int main() {

    // Floating-point types store values in binary, and most decimal
    // fractions have no exact binary form - the same way 1/3 has no
    // exact decimal form. So small representational errors creep in.

    double a{0.1};
    double b{0.2};
    double sum{a + b};

    std::println("0.1 + 0.2 = {:.17f}", sum);      // not exactly 0.3
    std::println("sum == 0.3 : {}", sum == 0.3);    // false

    // Don't compare floating-point values with == . Check that they're
    // close enough instead - within a small tolerance (epsilon).
    double epsilon{1e-9};
    bool close_enough{std::fabs(sum - 0.3) < epsilon};
    std::println("close to 0.3 within {}: {}", epsilon, close_enough);

    // Compound interest: money is where this bites, so format to exactly
    // 2 decimal places on output with the {:.2f} spec.
    double principal{1000.00};
    double rate{0.05};

    std::println("\n{:>4}  {:>18}", "Year", "Amount on deposit");
    for (int year{1}; year <= 10; ++year) {
        double amount{principal * std::pow(1.0 + rate, year)};
        std::println("{:>4}  {:>18.2f}", year, amount);
    }

    // The classic std::cout way needs stream manipulators (std::fixed,
    // std::setprecision(2) from <iomanip>) that stay in effect until
    // changed. The {:.2f} spec applies to just that one value - nothing
    // to set up beforehand or reset afterward.

    return 0;
}
