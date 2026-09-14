#include <print>
#include <chrono>
#include <ctime>

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

    // --- A quick tour of the standard's clock family -----------------------
    // Every clock pairs a time_point type with an epoch. now() gets the
    // current time_point; is_steady reports whether the clock can go
    // backward.
    //
    //   CLOCK                  EPOCH             NOTES
    //   system_clock            1970-01-01         wall-clock UTC, CAN jump
    //   steady_clock             unspecified        never goes backward
    //   high_resolution_clock    unspecified        shortest tick period -
    //                                                often just an alias for
    //                                                system_clock or
    //                                                steady_clock, so its
    //                                                behavior isn't portable.
    //                                                Prefer steady_clock for
    //                                                measuring, system_clock
    //                                                for wall-clock time.
    std::println("steady_clock::is_steady = {}", std::chrono::steady_clock::is_steady);
    std::println("system_clock::is_steady = {}", std::chrono::system_clock::is_steady);

    // system_clock additionally offers to_time_t()/from_time_t() to
    // interoperate with the C-style <ctime> time_t representation.
    std::time_t as_time_t{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
    auto back_to_time_point{std::chrono::system_clock::from_time_t(as_time_t)};
    std::println("round-tripped through time_t: {:%Y-%m-%d %H:%M:%S}",
             std::chrono::time_point_cast<std::chrono::seconds>(back_to_time_point));
}
