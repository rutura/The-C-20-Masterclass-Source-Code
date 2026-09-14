#include <print>
#include <ratio>

// std::ratio<Num, Den> is not a value you compute with at runtime - it is a
// TYPE. The numerator and denominator are compile-time constants baked into
// the type itself. This is the foundation chrono is built on: every duration
// type is tagged with a ratio describing its tick length.
int main() {
    using namespace std;

    // Define a compile-time rational number: 1/60.
    using r1 = ratio<1, 60>;

    // Get numerator and denominator - both compile-time constants.
    intmax_t num{r1::num};
    intmax_t den{r1::den};
    println("1) r1 = {}/{}", num, den);

    // Add two rational numbers. Because this happens on TYPES, you cannot
    // write r1 + r2 - you use the ratio_add class template instead, and
    // read the result off its embedded ::type alias.
    using r2 = ratio<1, 30>;
    println("2) r2 = {}/{}", r2::num, r2::den);

    using result = ratio_add<r1, r2>::type;
    println("3) sum = {}/{}", result::num, result::den);   // 1/20, normalized

    // Ratio comparisons are also type-level, producing a bool_constant
    // (an integral_constant<bool, ...>) whose value you read via ::value.
    using res = ratio_less<r2, r1>;
    println("4) r2 < r1: {}", res::value);

    // A ratio is always normalized: for ratio<n, d>, the greatest common
    // divisor of n and d is divided out. ratio<2, 4> and ratio<1, 2> are
    // the exact same type.
    using unreduced = ratio<2, 4>;
    using reduced = ratio<1, 2>;
    println("5) ratio<2,4> == ratio<1,2>: {}",
             ratio_equal<unreduced, reduced>::value);

    // The library ships SI ratio aliases for convenience - milli, micro,
    // nano, kilo, mega, and so on - used throughout <chrono> to define
    // predefined duration types like milliseconds and microseconds.
    println("6) milli = {}/{}", milli::num, milli::den);
    println("7) kilo  = {}/{}", kilo::num, kilo::den);
}
