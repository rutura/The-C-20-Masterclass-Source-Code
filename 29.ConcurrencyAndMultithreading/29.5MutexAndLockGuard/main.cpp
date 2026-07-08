// The fix for the last lecture's race: a std::mutex ("mutual exclusion")
// only lets one thread at a time through the region it guards - every other
// thread trying to lock it simply waits its turn.

#include <print>
#include <thread>
#include <vector>
#include <mutex>

int main() {

    long long counter{0};
    constexpr int incrementsPerThread{100'000};
    constexpr int threadCount{4};

    std::mutex counterMutex;

    auto incrementManyTimes = [&counter, &counterMutex] {
        for (int i{}; i < incrementsPerThread; ++i) {
            // std::lock_guard locks counterMutex on construction and
            // unlocks it automatically when it goes out of scope at the
            // end of this block - even if an exception were thrown, the
            // unlock still happens (the same RAII idea SmartPointers used
            // for memory, now applied to a lock).
            std::lock_guard<std::mutex> guard(counterMutex);
            ++counter;
        }
    };

    std::vector<std::jthread> workers;
    for (int i{}; i < threadCount; ++i) {
        workers.emplace_back(incrementManyTimes);
    }
    workers.clear();

    long long expected = static_cast<long long>(threadCount) * incrementsPerThread;
    std::println("Expected counter : {}", expected);
    std::println("Actual counter   : {}", counter);
    std::println("Lost increments  : {}", expected - counter);
    // Always 0 now - every increment is protected, so nothing gets
    // overwritten by another thread mid-update. The tradeoff: only one
    // thread can increment at a time, so this is correct but slower than
    // the broken version - a cost every synchronization technique in this
    // chapter has to pay in one form or another.

    return 0;
}
