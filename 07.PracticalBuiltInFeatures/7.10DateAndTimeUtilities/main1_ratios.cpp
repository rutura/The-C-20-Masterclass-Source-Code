#include <print>
#include <ratio>

// std::ratio<Num, Den> is not a value you compute with at runtime - it is a
// TYPE. The numerator and denominator are compile-time constants baked into
// the type itself. This is the foundation chrono is built on: every duration
// type is tagged with a ratio describing its tick length - a quarter of an
// hour, a thousandth of a second, and so on.
int main() {
    using namespace std;

    // A quarter of an hour, spelled out in full - no alias yet.
    // Get the numerator and denominator off the TYPE itself.
    intmax_t quarterHourNum{ratio<1, 4>::num};
    intmax_t quarterHourDen{ratio<1, 4>::den};
    println("1) 1/4 = {}/{}", quarterHourNum, quarterHourDen);

    // A ratio is always normalized: the greatest common divisor of the
    // numerator and denominator is divided out. ratio<2, 8> and ratio<1, 4>
    // are the exact same TYPE, even though you wrote different numbers.
    println("2) ratio<2,8> == ratio<1,4>: {}",
             ratio_equal<ratio<2, 8>, ratio<1, 4>>::value);

    // --- The four arithmetic operations, spelled out in full --------------
    // Because ratios are TYPES, not objects, you cannot write
    // ratio<1,4> + ratio<1,3> - the arithmetic happens on the types,
    // through ratio_add/subtract/multiply/divide, and the answer comes
    // back as a new type via the embedded ::type alias.

    // Addition: a quarter of an hour + a third of an hour.
    using sumType = ratio_add<ratio<1, 4>, ratio<1, 3>>::type;
    println("3) 1/4 + 1/3 = {}/{}", sumType::num, sumType::den);   // 7/12

    // Subtraction: a half of an hour - a quarter of an hour.
    using differenceType = ratio_subtract<ratio<1, 2>, ratio<1, 4>>::type;
    println("4) 1/2 - 1/4 = {}/{}", differenceType::num, differenceType::den);   // 1/4

    // Multiplication: a quarter of an hour, times two-thirds.
    using productType = ratio_multiply<ratio<1, 4>, ratio<2, 3>>::type;
    println("5) 1/4 * 2/3 = {}/{}", productType::num, productType::den);   // 1/6

    // Division: a half, divided by a quarter.
    using quotientType = ratio_divide<ratio<1, 2>, ratio<1, 4>>::type;
    println("6) (1/2) / (1/4) = {}/{}", quotientType::num, quotientType::den);   // 2/1

    // --- Comparisons, also at compile time ---------------------------------
    // ratio_equal, ratio_not_equal, ratio_less, ratio_less_equal,
    // ratio_greater, and ratio_greater_equal all produce a std::bool_constant -
    // itself a std::integral_constant<bool, ...> - whose value you read
    // through ::value.
    println("7) 1/3 <  1/4 : {}", (ratio_less<ratio<1, 3>, ratio<1, 4>>::value));
    println("8) 1/3 >  1/4 : {}", (ratio_greater<ratio<1, 3>, ratio<1, 4>>::value));
    println("9) 1/4 <= 1/4 : {}", (ratio_less_equal<ratio<1, 4>, ratio<1, 4>>::value));

    // --- Naming a ratio with `using`, once you're tired of spelling it out -
    // A type alias is just a shorter name for the exact same type - it
    // changes nothing about how the ratio behaves.
    using quarterHour = ratio<1, 4>;
    using thirdHour = ratio<1, 3>;
    using sumViaAliases = ratio_add<quarterHour, thirdHour>::type;
    println("10) quarterHour + thirdHour = {}/{}",
             sumViaAliases::num, sumViaAliases::den);   // same 7/12 as line 3

    // --- SI ratio aliases the library ships for convenience -----------------
    // milli, micro, nano, kilo, mega, and more - chrono uses exactly these
    // to define its predefined duration types (milliseconds ticks in
    // milli-second units, for example).
    println("11) milli = {}/{}", milli::num, milli::den);
    println("12) kilo  = {}/{}", kilo::num, kilo::den);
}
