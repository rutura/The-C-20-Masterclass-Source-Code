#include <print>
#include <chrono>

// time_points, like durations, can convert implicitly when no information
// is lost, and require an explicit cast otherwise.
int main() {
    using namespace std::chrono_literals;

    {
        // Going from a coarser tick (seconds) to a finer one (milliseconds)
        // never loses information, so it happens implicitly.
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::seconds> tpSeconds{42s};
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>
            tpMilliseconds{tpSeconds};

        std::println("{}", tpMilliseconds.time_since_epoch());   // 42000ms
    }

    {
        // Going from a finer tick (milliseconds) to a coarser one (seconds)
        // COULD lose information (leftover milliseconds don't fit in whole
        // seconds), so it requires the explicit time_point_cast<T>() -
        // exactly the same idea as duration_cast<T>() for durations.
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>
            tpMilliseconds{42'424ms};

        std::chrono::time_point<std::chrono::steady_clock, std::chrono::seconds> tpSeconds{
            std::chrono::time_point_cast<std::chrono::seconds>(tpMilliseconds)};
        // Or, letting the compiler deduce the type:
        //   auto tpSeconds{std::chrono::time_point_cast<std::chrono::seconds>(tpMilliseconds)};

        // Converting back to milliseconds shows the lost precision: 42424ms
        // became 42000ms, not the original value.
        std::chrono::milliseconds ms{tpSeconds.time_since_epoch()};
        std::println("{}", ms);   // 42000ms
    }

    // floor(), ceil(), and round() work on time_points exactly as they do
    // on plain numeric values - each rounds toward a given duration
    // granularity instead of just truncating.
    {
        std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>
            tp{2'500ms};
        std::println("floor<seconds> : {}",
                      std::chrono::floor<std::chrono::seconds>(tp).time_since_epoch());
        std::println("ceil<seconds>  : {}",
                      std::chrono::ceil<std::chrono::seconds>(tp).time_since_epoch());
        std::println("round<seconds> : {}",
                      std::chrono::round<std::chrono::seconds>(tp).time_since_epoch());
    }
}
