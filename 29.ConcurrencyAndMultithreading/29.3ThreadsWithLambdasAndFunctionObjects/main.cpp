// The last lecture handed a thread a named free function. In practice you
// almost always hand it a lambda instead - captures let it carry along
// exactly the data it needs, no separate parameter list required at the
// call site.

#include <print>
#include <thread>
#include <vector>

int main() {

    int multiplier{10};

    // A lambda capturing by value - the thread gets its own copy of
    // multiplier, safe even if main()'s multiplier changed afterward.
    std::jthread byValue([multiplier] {
        std::println("byValue thread: multiplier = {}", multiplier);
    });
    byValue.join();

    // A lambda capturing by reference - the thread reads/writes the
    // caller's actual variable. Safe here only because main() waits (joins)
    // before multiplier goes out of scope - the next lecture shows what
    // goes wrong when several threads share access like this without
    // coordinating.
    std::jthread byReference([&multiplier] {
        multiplier *= 2;
        std::println("byReference thread: multiplier now = {}", multiplier);
    });
    byReference.join();
    std::println("main() sees multiplier = {}", multiplier);

    // A function object (a class with operator()) works too - useful when
    // the thread's logic needs its own state beyond what a capture list
    // conveniently carries.
    struct Counter {
        int start;
        void operator()() const {
            for (int i{}; i < 3; ++i) {
                std::println("Counter thread: {}", start + i);
            }
        }
    };
    std::jthread withFunctor(Counter{100});
    withFunctor.join();

    // Launching several threads at once and joining them all - a
    // std::vector<std::jthread> lets you scale this to any number of
    // workers instead of naming each one.
    std::vector<std::jthread> workers;
    for (int i{}; i < 3; ++i) {
        workers.emplace_back([i] {
            std::println("worker {} running", i);
        });
    }
    // Each std::jthread joins automatically in its own destructor when
    // `workers` is destroyed at the end of main() - no explicit loop needed.

    return 0;
}
