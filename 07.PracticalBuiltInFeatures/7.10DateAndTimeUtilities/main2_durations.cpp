#include <print>
#include <chrono>
#include <ratio>

// std::chrono::duration<Rep, Period> stores a count of ticks (Rep) and a
// tick length (Period, a compile-time std::ratio in seconds). The default
// Period is ratio<1> - one tick equals one second.
int main() {
    // A duration where each tick is 60 seconds (i.e., minutes), holding 123
    // ticks -> 123 minutes.
    std::chrono::duration<long, std::ratio<60>> d1{123};
    std::println("{} ({})", d1, d1.count());

    // A duration represented by a double, tick = 1 second, set to the
    // largest value that type can hold.
    auto d2{std::chrono::duration<double>::max()};
    std::println("{}", d2);

    // Two durations with different tick periods: d3 ticks in minutes,
    // d4 ticks in seconds.
    std::chrono::duration<long, std::ratio<60>> d3{10};   // 10 minutes
    std::chrono::duration<long, std::ratio<1>> d4{14};    // 14 seconds

    // Comparison operators work across different Rep/Period combinations -
    // the library converts internally to compare correctly.
    if (d3 > d4) { std::println("d3 > d4"); }
    else { std::println("d3 <= d4"); }

    // Durations support the usual arithmetic operators.
    ++d4;      // 14 -> 15 seconds
    d4 *= 2;   // 15 -> 30 seconds

    // Adding d3 (minutes) and d4 (seconds) and storing the result as a
    // floating-point duration in minutes.
    std::chrono::duration<double, std::ratio<60>> d5{d3 + d4};
    // Same sum, stored as an integral duration in seconds instead.
    std::chrono::duration<long, std::ratio<1>> d6{d3 + d4};
    std::println("{} + {} = {} or {}", d3, d4, d5, d6);

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

    // --- Predefined durations -------------------------------------------
    // The standard ships named aliases so you rarely spell out
    // duration<Rep, Period> yourself: seconds, minutes, hours, milliseconds,
    // microseconds, nanoseconds, days, weeks, months, years.
    auto t{std::chrono::hours{1} + std::chrono::minutes{23} + std::chrono::seconds{45}};
    std::println("{}", std::chrono::seconds{t});

    // Predefined durations use INTEGRAL Reps by standard mandate, so a
    // conversion that could produce a fractional result is a compile-time
    // error, even when the actual numbers happen to divide evenly:
    //   seconds s{60};
    //   minutes m{s};        // Error: could lose a fractional remainder
    // Converting minutes -> seconds is always exact, so it stays implicit:
    std::chrono::minutes m{2};
    std::chrono::seconds s{m};
    std::println("{} minutes = {}", m.count(), s);

    // --- Standard chrono literals -----------------------------------------
    // h, min, s, ms, us, ns build durations directly from numeric literals.
    // The literals themselves live in std::chrono_literals - this using
    // directive brings in ONLY the literal suffixes, not all of std::chrono.
    using namespace std::chrono_literals;
    auto myDuration{42min};
    std::println("{}", myDuration);

    // --- hh_mm_ss: splitting a duration into display-friendly fields ------
    // hh_mm_ss accepts any duration and exposes hours()/minutes()/seconds()/
    // subseconds() getters, always non-negative, plus is_negative().
    const std::chrono::hh_mm_ss split{t};
    std::println("{}h {}m {}s (negative? {})",
             split.hours().count(), split.minutes().count(),
             split.seconds().count(), split.is_negative());
}
