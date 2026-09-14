#include <print>
#include <ratio>
#include <cstdint>

// std::ratio<Num, Den> is not a value you compute with at runtime - it is a
// TYPE. The numerator and denominator are compile-time constants baked into
// the type itself. This is the foundation chrono is built on: every duration
// type is tagged with a ratio describing its tick length - a quarter of an
// hour, a thousandth of a second, and so on.
int main() {
    // A quarter of an hour, spelled out in full - no alias yet.
    // Get the numerator and denominator off the TYPE itself.
    std::intmax_t quarter_hour_num{std::ratio<1, 4>::num};
    std::intmax_t quarter_hour_den{std::ratio<1, 4>::den};
    std::println("1) 1/4 = {}/{}", quarter_hour_num, quarter_hour_den);

    // A ratio is always normalized: the greatest common divisor of the
    // numerator and denominator is divided out. ratio<2, 8> and ratio<1, 4>
    // are the exact same TYPE, even though you wrote different numbers.
    std::println("2) ratio<2,8> == ratio<1,4>: {}",
             std::ratio_equal<std::ratio<2, 8>, std::ratio<1, 4>>::value);

    // --- Naming a ratio with `using`, once you're tired of spelling it out -
    // A type alias is just a shorter name for the exact same type - it
    // changes nothing about how the ratio behaves.
    using quarter_hour = std::ratio<1, 4>;
    using third_hour = std::ratio<1, 3>;
    using sum_via_aliases = std::ratio_add<quarter_hour, third_hour>::type;
    std::println("3) quarter_hour + third_hour = {}/{}",
             sum_via_aliases::num, sum_via_aliases::den);   // same 7/12 as line 3

    // --- The four arithmetic operations, spelled out in full --------------
    // Because ratios are TYPES, not objects, you cannot write
    // ratio<1,4> + ratio<1,3> - the arithmetic happens on the types,
    // through ratio_add/subtract/multiply/divide, and the answer comes
    // back as a new type via the embedded ::type alias.

    // Addition: a quarter of an hour + a third of an hour.
    using sum_type = std::ratio_add<std::ratio<1, 4>, std::ratio<1, 3>>::type;
    std::println("4) 1/4 + 1/3 = {}/{}", sum_type::num, sum_type::den);   // 7/12

    // Subtraction: a half of an hour - a quarter of an hour.
    using diff_type = std::ratio_subtract<std::ratio<1, 2>, std::ratio<1, 4>>::type;
    std::println("5) 1/2 - 1/4 = {}/{}", diff_type::num, diff_type::den);   // 1/4

    // Multiplication: a quarter of an hour, times two-thirds.
    using product_type = std::ratio_multiply<std::ratio<1, 4>, std::ratio<2, 3>>::type;
    std::println("6) 1/4 * 2/3 = {}/{}", product_type::num, product_type::den);   // 1/6

    // Division: a half, divided by a quarter.
    using quotient_type = std::ratio_divide<std::ratio<1, 2>, std::ratio<1, 4>>::type;
    std::println("7) (1/2) / (1/4) = {}/{}", quotient_type::num, quotient_type::den);   // 2/1

    // --- Comparisons, also at compile time ---------------------------------
    // ratio_equal, ratio_not_equal, ratio_less, ratio_less_equal,
    // ratio_greater, and ratio_greater_equal all produce a std::bool_constant -
    // itself a std::integral_constant<bool, ...> - whose value you read
    // through ::value.
    std::println("8) 1/3 <  1/4 : {}", (std::ratio_less<std::ratio<1, 3>, std::ratio<1, 4>>::value));
    std::println("9) 1/3 >  1/4 : {}", (std::ratio_greater<std::ratio<1, 3>, std::ratio<1, 4>>::value));
    std::println("10) 1/4 <= 1/4 : {}", (std::ratio_less_equal<std::ratio<1, 4>, std::ratio<1, 4>>::value));


    // --- SI ratio aliases the library ships for convenience -----------------
    // milli, micro, nano, kilo, mega, and more - chrono uses exactly these
    // to define its predefined duration types (milliseconds ticks in
    // milli-second units, for example).
    std::println("11) milli = {}/{}", std::milli::num, std::milli::den);
    std::println("12) kilo  = {}/{}", std::kilo::num, std::kilo::den);
}
