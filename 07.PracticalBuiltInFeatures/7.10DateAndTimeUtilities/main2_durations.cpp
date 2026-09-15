#include <print>
#include <chrono>
#include <ratio>

int main() {
    // The library ships a ready-made duration type for every unit you'd
    // normally reach for - no setup required.
    std::chrono::minutes five_minutes{5};
    std::println("{} ({})", five_minutes, five_minutes.count());

    // --- Standard chrono literals -----------------------------------------
    // h, min, s, ms, us, ns build durations directly from numeric literals.
    // The literals themselves live in std::chrono_literals - this using
    // directive brings in ONLY the literal suffixes, not all of std::chrono.
    using namespace std::chrono_literals;
    auto my_duration{42min};
    std::println("{}", my_duration);

    // Durations with different units mix freely in arithmetic and
    // comparisons - the library converts internally, no manual conversion
    // needed.
    std::chrono::minutes d3{10};   // 10 minutes
    std::chrono::seconds d4{14};   // 14 seconds
    if (d3 > d4) { std::println("d3 > d4"); }
    else { std::println("d3 <= d4"); }

    // Durations support the usual arithmetic operators.
    ++d4;      // 14 -> 15 seconds
    d4 *= 2;   // 15 -> 30 seconds

    // Adding minutes and seconds directly - chrono picks a common unit.
    auto race_duration{90min + 32s};
    std::println("{}", race_duration);

    // Recall from main1_ratios.cpp that ratio<Num, Den> defaults Den to 1 -
    // ratio<60> and ratio<60, 1> are the exact same type, just spelled
    // differently. Declaring one without a denominator and reading its
    // num/den back off the type proves the 1 is really there.
    std::println("{}/{}", std::ratio<60>::num, std::ratio<60>::den);
    std::println("{}", std::ratio_equal<std::ratio<60>, std::ratio<60, 1>>::value);

    // --- Under the hood: duration<Rep, Period> -----------------------------
    // Every duration type above - minutes included - is really the same
    // template: a plain number (Rep), paired with a compile-time ratio
    // (Period) saying how many seconds long ONE TICK is. std::chrono::minutes
    // is nothing more than duration<some integer type, ratio<60>> under a
    // shorter name. Spelling it out yourself lets you describe a unit the
    // library doesn't name for you.
    //
    //   std::chrono::duration<Rep, Period>
    //                          |     |
    //                          |     +-- tick period, a compile-time ratio in
    //                          |         seconds - defaults to ratio<1>, i.e.
    //                          |         one tick = one second
    //                          +-------- the type holding the tick COUNT
    //                                    (an arithmetic type: long, double, ...)

    // A duration where each tick is 60 seconds (i.e., minutes), holding 123
    // ticks -> 123 minutes.
    std::chrono::duration<long, std::ratio<60>> d1{123};
    std::println("{} ({})", d1, d1.count());

    // A duration can just as easily tick FASTER than a second. ratio<1, 1000>
    // means "one tick is 1/1000 of a second" - 250 of those ticks is a
    // quarter of a second. This is exactly how std::chrono::milliseconds is
    // built, just spelled out by hand instead of using the predefined alias.
    std::chrono::duration<long, std::ratio<1, 1000>> d1_ms{250};
    std::println("{} ({})", d1_ms, d1_ms.count());

    // A duration represented by a double, tick = 1 second, set to the
    // largest value that type can hold.
    auto d2{std::chrono::duration<double>::max()};
    std::println("{}", d2);

    // --- Converting between duration types ----------------------------------
    // Converting an integral seconds-duration to minutes needs a
    // floating-point representation, because the result (0.5 minutes)
    // is not a whole number of minutes. This conversion is IMPLICIT
    // because going from a smaller tick to a bigger tick with a
    // floating-point Rep can never lose information.
    std::chrono::duration<long> d7{30};                        // 30 seconds
    std::chrono::duration<double, std::ratio<60>> d8{d7};      // 0.5 minutes
    std::println("{} = {}", d7, d8);
    std::println("{} seconds = {} minutes", d7.count(), d8.count());

    // The following would NOT compile:
    //   duration<long, ratio<60>> d8_bad{d7};   // Error: possible truncation
    // Converting seconds -> minutes with an INTEGRAL Rep could produce a
    // non-integral number of minutes, so the compiler refuses the implicit
    // conversion. duration_cast<T>() forces it anyway, using integer
    // division/truncation - here, 30 seconds truncates to 0 minutes.
    auto d8_forced{std::chrono::duration_cast<
        std::chrono::duration<long, std::ratio<60>>>(d7)};
    std::println("{}", d8_forced);

    // Converting the OTHER direction - minutes to seconds - never loses
    // information when both Reps are integral, so it stays implicit.
    std::chrono::duration<long, std::ratio<60>> d9{10};   // 10 minutes
    std::chrono::duration<long> d10{d9};                    // 600 seconds
    std::println("{}", d10);

    // Predefined durations use INTEGRAL Reps by standard mandate, so a
    // conversion that could produce a fractional result is a compile-time
    // error, even when the actual numbers happen to divide evenly:
    //   seconds s{60};
    //   minutes m{s};        // Error: could lose a fractional remainder
    // Converting minutes -> seconds is always exact, so it stays implicit:
    std::chrono::minutes m{2};
    std::chrono::seconds s{m};
    std::println("{} minutes = {}", m.count(), s);

    // --- hh_mm_ss: splitting a duration into display-friendly fields ------
    // hh_mm_ss accepts any duration and exposes hours()/minutes()/seconds()/
    // subseconds() getters, always non-negative, plus is_negative().
    auto t{std::chrono::hours{1} + std::chrono::minutes{23} + std::chrono::seconds{45}};
    std::println("{}", std::chrono::seconds{t});
    const std::chrono::hh_mm_ss split{t};
    std::println("{}h {}m {}s (negative? {})",
             split.hours().count(), split.minutes().count(),
             split.seconds().count(), split.is_negative());
}
