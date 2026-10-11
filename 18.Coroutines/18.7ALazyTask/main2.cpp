#include <print>

#include "task.h"

// How deep can a chain of tasks go? Every co_await below starts a task that
// finishes at once and hands control back (the symmetric transfer of
// FinalAwaiter in task.h). If that hand-back were an ordinary nested call, a
// million of them would use a million stack frames.

Task<int> one() {
    co_return 1;
}

Task<long long> add_up(int count) {
    long long total{0};
    for (int i{0}; i < count; ++i) {
        total += co_await one();
    }
    co_return total;
}

int main() {
    std::println("{}", add_up(1'000'000).get());
    return 0;
}
