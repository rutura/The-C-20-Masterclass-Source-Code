#include <print>
#include <chrono>

// time_points, like durations, can convert implicitly when no information
// is lost, and require an explicit cast otherwise.
int main() {
    using namespace std;
    using namespace std::chrono;

    {
        // Going from a coarser tick (seconds) to a finer one (milliseconds)
        // never loses information, so it happens implicitly.
        time_point<steady_clock, seconds> tp_seconds{42s};
        time_point<steady_clock, milliseconds> tp_milliseconds{tp_seconds};

        println("{}", tp_milliseconds.time_since_epoch());   // 42000ms
    }

    {
        // Going from a finer tick (milliseconds) to a coarser one (seconds)
        // COULD lose information (leftover milliseconds don't fit in whole
        // seconds), so it requires the explicit time_point_cast<T>() -
        // exactly the same idea as duration_cast<T>() for durations.
        time_point<steady_clock, milliseconds> tp_milliseconds{42'424ms};

        time_point<steady_clock, seconds> tp_seconds{
            time_point_cast<seconds>(tp_milliseconds)};
        // Or, letting the compiler deduce the type:
        //   auto tp_seconds{time_point_cast<seconds>(tp_milliseconds)};

        // Converting back to milliseconds shows the lost precision: 42424ms
        // became 42000ms, not the original value.
        milliseconds ms{tp_seconds.time_since_epoch()};
        println("{}", ms);   // 42000ms
    }

    // floor(), ceil(), and round() work on time_points exactly as they do
    // on plain numeric values - each rounds toward a given duration
    // granularity instead of just truncating.
    {
        time_point<steady_clock, milliseconds> tp{2'500ms};
        println("floor<seconds> : {}", floor<seconds>(tp).time_since_epoch());
        println("ceil<seconds>  : {}", ceil<seconds>(tp).time_since_epoch());
        println("round<seconds> : {}", round<seconds>(tp).time_since_epoch());
    }
}
