// The last lecture's byReference example was safe only because main()
// joined the thread before touching multiplier again - one thread at a
// time ever touched it. A race condition happens when two or more threads
// read-modify-write the *same* variable at the *same* time, with nothing
// coordinating them - the two threads' updates can interleave and one gets
// silently lost.

#include <print>
#include <thread>
#include <vector>

int main() {

    long long counter{0};
    constexpr int incrementsPerThread{100'000};
    constexpr int threadCount{4};

    // Every thread runs this same loop against the *same* counter, with no
    // coordination at all.
    auto incrementManyTimes = [&counter] {
        for (int i{}; i < incrementsPerThread; ++i) {
            ++counter; // NOT atomic: read counter, add 1, write counter back -
                       // three separate steps another thread can interleave with
        }
    };

    std::vector<std::jthread> workers;
    for (int i{}; i < threadCount; ++i) {
        workers.emplace_back(incrementManyTimes);
    }
    workers.clear(); // clearing the vector destroys each jthread, which joins it

    long long expected = static_cast<long long>(threadCount) * incrementsPerThread;
    std::println("Expected counter : {}", expected);
    std::println("Actual counter   : {}", counter);
    std::println("Lost increments  : {}", expected - counter);

    // Run it again - the lost-increment count differs (or is sometimes 0
    // by luck) every run. That unpredictability *is* the bug: ++counter
    // isn't guaranteed to be safe across threads just because it looks like
    // one operation in source code. The next few lectures fix this three
    // different ways.

    return 0;
}
