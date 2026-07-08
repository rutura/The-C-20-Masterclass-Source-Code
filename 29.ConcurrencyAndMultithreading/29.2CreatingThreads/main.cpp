// Every program you've written so far runs one instruction at a time, in
// one order. A thread is a second (or third, or Nth) independent sequence
// of instructions running alongside main() - genuinely at the same time on
// a multi-core machine, not just interleaved.

#include <print>
#include <thread>

void greet(const std::string& name) {
    std::println("Hello from thread, {}!", name);
}

int main() {

    std::println("main() starting");

    // std::jthread (C++20) is the modern default: it automatically joins
    // (waits for the thread to finish) in its destructor, so forgetting to
    // call join() - a genuine crash-causing bug with the older
    // std::thread - simply can't happen here.
    std::jthread worker(greet, "Alice");

    std::println("main() doing other work while worker runs...");

    // worker's destructor joins automatically when it goes out of scope at
    // the end of main() - no explicit worker.join() needed, unlike
    // std::thread.
    std::println("main() finishing");

    return 0;
}
