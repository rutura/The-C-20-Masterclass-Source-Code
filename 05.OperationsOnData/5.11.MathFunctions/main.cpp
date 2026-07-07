#include <print>
#include <cmath>

int main() {

    // <cmath> gives us the common math operations a budgeting app needs
    // beyond the basic + - * / from earlier in this chapter.

    double averageExpense{7.7};

    // floor/ceil: round down or up to the nearest whole number - handy for
    // "round down to the nearest dollar" vs. "round up to be safe".
    std::println("averageExpense rounded down (floor): {}", std::floor(averageExpense));
    std::println("averageExpense rounded up (ceil)   : {}", std::ceil(averageExpense));

    // abs: distance from zero, regardless of sign - useful since an overdrawn
    // balance is negative, but "how much are we over by" should read as positive.
    double accountBalance{-5000};
    std::println("abs(averageExpense) : {}", std::abs(averageExpense));
    std::println("abs(accountBalance) : {}", std::abs(accountBalance));

    // pow: raising a number to a power - the basis for compound interest,
    // where a balance grows by a fixed rate every period.
    std::println("");
    std::println("3 ^ 4 is: {}", std::pow(3, 4));
    std::println("9 ^ 3 is: {}", std::pow(9, 3));

    // exp: e^x - one building block of continuous compound interest formulas.
    double exponential = std::exp(10);
    std::println("e ^ 10 is: {}", exponential);

    // log/log10: the reverse of pow - "to what power must I raise this base
    // to get this number?" Useful for working out how many compounding
    // periods it takes a balance to reach a target.
    std::println("");
    std::println("log base e: to reach 54.59, raise e to the power of {}", std::log(54.59));
    std::println("log base 10: to reach 10000, raise 10 to the power of {}", std::log10(10000)); // 4

    // sqrt: square root.
    std::println("");
    std::println("sqrt(81) is: {}", std::sqrt(81));

    // round: rounds to the nearest whole number; exact halfway points round
    // away from zero (2.5 rounds to 3, not 2) - worth knowing before you rely
    // on it to round a price to the nearest dollar.
    std::println("");
    std::println("3.654 rounds to: {}", std::round(3.654));
    std::println("2.5 rounds to  : {}", std::round(2.5));
    std::println("2.4 rounds to  : {}", std::round(2.4));

    return 0;
}
