#include <print>
#include <chrono>
#include <ratio>

// std::chrono::duration<Rep, Period> stores a count of ticks (Rep) and a
// tick length (Period, a compile-time std::ratio in seconds). The default
// Period is ratio<1> - one tick equals one second.
int main() {
    using namespace std;
    using namespace std::chrono;

    // A duration where each tick is 60 seconds (i.e., minutes), holding 123
    // ticks -> 123 minutes.
    duration<long, ratio<60>> d1{123};
    println("{} ({})", d1, d1.count());

    // A duration represented by a double, tick = 1 second, set to the
    // largest value that type can hold.
    auto d2{duration<double>::max()};
    println("{}", d2);

    // Two durations with different tick periods: d3 ticks in minutes,
    // d4 ticks in seconds.
    duration<long, ratio<60>> d3{10};   // 10 minutes
    duration<long, ratio<1>> d4{14};    // 14 seconds

    // Comparison operators work across different Rep/Period combinations -
    // the library converts internally to compare correctly.
    if (d3 > d4) { println("d3 > d4"); }
    else { println("d3 <= d4"); }

    // Durations support the usual arithmetic operators.
    ++d4;      // 14 -> 15 seconds
    d4 *= 2;   // 15 -> 30 seconds

    // Adding d3 (minutes) and d4 (seconds) and storing the result as a
    // floating-point duration in minutes.
    duration<double, ratio<60>> d5{d3 + d4};
    // Same sum, stored as an integral duration in seconds instead.
    duration<long, ratio<1>> d6{d3 + d4};
    println("{} + {} = {} or {}", d3, d4, d5, d6);

    // Converting an integral seconds-duration to minutes needs a
    // floating-point representation, because the result (0.5 minutes)
    // is not a whole number of minutes. This conversion is IMPLICIT
    // because going from a smaller tick to a bigger tick with a
    // floating-point Rep can never lose information.
    duration<long> d7{30};                  // 30 seconds
    duration<double, ratio<60>> d8{d7};      // 0.5 minutes
    println("{} = {}", d7, d8);
    println("{} seconds = {} minutes", d7.count(), d8.count());

    // The following would NOT compile:
    //   duration<long, ratio<60>> d8_bad{d7};   // Error: possible truncation
    // Converting seconds -> minutes with an INTEGRAL Rep could produce a
    // non-integral number of minutes, so the compiler refuses the implicit
    // conversion. duration_cast<T>() forces it anyway, using integer
    // division/truncation - here, 30 seconds truncates to 0 minutes.
    auto d8_forced{duration_cast<duration<long, ratio<60>>>(d7)};
    println("{}", d8_forced);

    // Converting the OTHER direction - minutes to seconds - never loses
    // information when both Reps are integral, so it stays implicit.
    duration<long, ratio<60>> d9{10};   // 10 minutes
    duration<long> d10{d9};              // 600 seconds
    println("{}", d10);

    // --- Predefined durations -------------------------------------------
    // The standard ships named aliases so you rarely spell out
    // duration<Rep, Period> yourself: seconds, minutes, hours, milliseconds,
    // microseconds, nanoseconds, days, weeks, months, years.
    auto t{hours{1} + minutes{23} + seconds{45}};
    println("{}", seconds{t});

    // Predefined durations use INTEGRAL Reps by standard mandate, so a
    // conversion that could produce a fractional result is a compile-time
    // error, even when the actual numbers happen to divide evenly:
    //   seconds s{60};
    //   minutes m{s};        // Error: could lose a fractional remainder
    // Converting minutes -> seconds is always exact, so it stays implicit:
    minutes m{2};
    seconds s{m};
    println("{} minutes = {}", m.count(), s);

    // --- Standard chrono literals -----------------------------------------
    // h, min, s, ms, us, ns build durations directly from numeric literals.
    auto my_duration{42min};
    println("{}", my_duration);

    // --- hh_mm_ss: splitting a duration into display-friendly fields ------
    // hh_mm_ss accepts any duration and exposes hours()/minutes()/seconds()/
    // subseconds() getters, always non-negative, plus is_negative().
    const hh_mm_ss split{t};
    println("{}h {}m {}s (negative? {})",
             split.hours().count(), split.minutes().count(),
             split.seconds().count(), split.is_negative());
}
