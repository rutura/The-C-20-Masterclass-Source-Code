// The mutex from 34.5 fixed the race condition by making every thread wait
// its turn - correct, but the waiting itself has a cost. For something as
// simple as "increment a counter," std::atomic gives the same correctness
// without a lock: the hardware itself guarantees the read-modify-write
// happens as one indivisible step.

#include <print>
#include <thread>
#include <vector>
#include <atomic>

int main() {

    std::atomic<long long> counter{0};
    constexpr int incrementsPerThread{100'000};
    constexpr int threadCount{4};

    auto incrementManyTimes = [&counter] {
        for (int i{}; i < incrementsPerThread; ++i) {
            ++counter; // std::atomic overloads ++ to be a single atomic
                       // operation - no lock/unlock needed, and no other
                       // thread's increment can interleave with it
        }
    };

    std::vector<std::jthread> workers;
    for (int i{}; i < threadCount; ++i) {
        workers.emplace_back(incrementManyTimes);
    }
    workers.clear();

    long long expected = static_cast<long long>(threadCount) * incrementsPerThread;
    std::println("Expected counter : {}", expected);
    std::println("Actual counter   : {}", counter.load());
    std::println("Lost increments  : {}", expected - counter.load());
    // Always 0, same guarantee as the mutex version - but no thread ever
    // blocks waiting for another to finish.

    // --- Not every operation you'd want is atomic just by wrapping the
    // type - only what std::atomic itself provides is guaranteed atomic ---
    std::atomic<int> flag{0};
    flag.store(1);                 // atomic write
    int current = flag.load();     // atomic read
    std::println("");
    std::println("flag after store/load : {}", current);

    // compare_exchange_strong: "if flag is still `expected`, set it to
    // `desired`; either way, tell me what it actually was" - the building
    // block lock-free algorithms use instead of a mutex.
    int expectedValue{1};
    bool changed = flag.compare_exchange_strong(expectedValue, 99);
    std::println("compare_exchange_strong succeeded : {}", changed);
    std::println("flag is now : {}", flag.load());

    return 0;
}
