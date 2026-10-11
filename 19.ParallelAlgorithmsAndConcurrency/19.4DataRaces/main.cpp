#include <cstddef>
#include <functional>
#include <print>
#include <thread>
#include <vector>

// The weather network has four stations. Each reports 1,000,000 readings, and
// we want to count them all in ONE shared counter. Four threads, one counter.
// What could go wrong?

constexpr int station_count{4};
constexpr int readings_per_station{1'000'000};

// ---- 1. The unprotected counter ------------------------------------------------------
// `++counter` looks like one step. It is three:
//
//     1. read the value from memory into a register
//     2. add one
//     3. write the result back
//
// Two threads can both do step 1 before either does step 3:
//
//     thread A: read 41 ............ add -> 42 ............ write 42
//     thread B: ........ read 41 ............ add -> 42 ............ write 42
//
// Two increments happened, and the counter went up by one: an update was LOST.
void count_readings_unprotected(int& counter) {
    for (int i{0}; i < readings_per_station; ++i) {
        ++counter;
    }
}

// ---- 2. Share nothing ----------------------------------------------------------------------
// The cheapest cure is not to share. Each thread counts into its OWN variable,
// and the partial counts are added together after join().
void count_readings_alone(int& my_count) {
    int local{0};
    for (int i{0}; i < readings_per_station; ++i) {
        ++local;
    }
    my_count = local;
}

int main() {
    const int expected{station_count * readings_per_station};

    std::println("--- an unprotected counter");
    int counter{0};
    {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings_unprotected, std::ref(counter));
        }
    }
    std::println("[varies] expected {}, got {}", expected, counter);
    std::println("[varies] updates lost: {}", expected - counter);

    std::println("\n--- each thread counts its own");
    std::vector<int> per_station(station_count, 0);
    {
        std::vector<std::jthread> stations;
        for (int i{0}; i < station_count; ++i) {
            stations.emplace_back(count_readings_alone, std::ref(per_station[static_cast<std::size_t>(i)]));
        }
    }
    int total{0};
    for (int count : per_station) {
        total += count;
    }
    std::println("expected {}, got {}", expected, total);

    // The first result is different on every run, and on every machine. It is
    // not just "a bit off": a data race is UNDEFINED BEHAVIOR. The compiler
    // is allowed to assume that it never happens, and may keep `counter` in a
    // register for the whole loop, reorder reads and writes, or do anything
    // else that is correct only for ONE thread.
    //
    // A DATA RACE is:  two threads access the same memory location,
    //                  at least one of them writes,
    //                  and nothing orders the accesses.
    // Reading from several threads is fine. Writing from one thread to memory
    // that nobody else uses is fine. The combination is the problem.
    return 0;
}
