#include <print>
#include <chrono>

// A time_point represents a point in time, stored internally as a duration
// relative to its clock's EPOCH - the moment that clock starts counting
// from. Every time_point is tied to a specific clock; the epoch belongs to
// that clock, not to time_point itself.
int main() {
    // Create a time_point representing the epoch of steady_clock (i.e., the
    // duration since epoch is zero).
    std::chrono::time_point<std::chrono::steady_clock> tp1;
    // Equivalent, using the clock's own nested time_point alias:
    //   std::chrono::steady_clock::time_point tp1;

    // time_points and durations support the arithmetic that makes sense:
    // time_point + duration -> time_point, time_point - time_point ->
    // duration. (time_point + time_point is NOT supported - adding two
    // points in time is meaningless.)
    tp1 += std::chrono::minutes{10};

    // time_since_epoch() returns the duration between the clock's epoch and
    // this time_point.
    auto d1{tp1.time_since_epoch()};

    // Convert that duration to a floating-point number of seconds and print
    // it.
    std::chrono::duration<double> d2{d1};
    std::println("{}", d2);   // 600s
}
