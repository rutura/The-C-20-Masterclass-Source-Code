#include <print>
#include <chrono>
#include <cmath>

// steady_clock is guaranteed to never go backward - unlike system_clock,
// which can jump when the OS clock is adjusted (NTP sync, a user changing
// the time). That makes steady_clock the right choice whenever you are
// MEASURING elapsed time rather than asking "what time is it."
int main() {
    // is_steady reports whether a clock's time_point can ever go backward.
    // steady_clock's is true - it's guaranteed to only ever move forward,
    // which is exactly why it's the right tool for measuring elapsed time.
    std::println("steady_clock::is_steady = {}", std::chrono::steady_clock::is_steady);

    // Get the start time.
    auto start{std::chrono::steady_clock::now()};

    // Some work to time - arithmetic heavy enough that the loop doesn't
    // finish instantly.
    const int number_of_iterations{10'000'000};
    double d{0};
    for (int i{0}; i < number_of_iterations; ++i) {
        d += std::sqrt(std::abs(std::sin(i) * std::cos(i)));
    }

    // Get the end time and calculate the difference - a duration, not a
    // time_point.
    auto end{std::chrono::steady_clock::now()};
    auto diff{end - start};

    // Use the result, otherwise an aggressive compiler might optimize the
    // entire loop away since d is never observed!
    std::println("d = {}", d);

    // Convert the difference into fractional milliseconds and print it.
    std::println("Total: {}", std::chrono::duration<double, std::milli>{diff});
    // duration_cast() gives whole milliseconds instead, if you don't need
    // the fractional part.
    std::println("Total: {}", std::chrono::duration_cast<std::chrono::milliseconds>(diff));
    // Time per iteration, in nanoseconds.
    std::println("{} per iteration",
                  std::chrono::duration<double, std::nano>{diff / number_of_iterations});

    // A note on accuracy: most OS timers only update every 10-15ms. Any
    // event shorter than one timer tick appears to take "zero" time, and
    // any event between one and two ticks appears to take exactly one tick -
    // a phenomenon called GATING ERROR. If your timings look suspiciously
    // small or suspiciously round, increase number_of_iterations so the
    // total time spans many timer ticks.
}
