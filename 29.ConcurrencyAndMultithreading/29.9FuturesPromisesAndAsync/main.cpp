// Every synchronization tool so far has been about threads sharing data
// safely. But often you just want to run something on another thread and
// get its *result* back later - std::future is exactly that: a handle to a
// value some other thread will eventually produce.

#include <print>
#include <thread>
#include <future>
#include <stdexcept>
#include <string>

int slowSquare(int value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return value * value;
}

int main() {

    // --- std::async: the simple, common case ---
    // std::launch::async forces this to actually run on a separate thread
    // (without it, the standard library is allowed to defer running it
    // until .get() is called, on the calling thread instead).
    std::future<int> squareFuture = std::async(std::launch::async, slowSquare, 12);

    std::println("Doing other work while slowSquare runs...");

    // .get() blocks until the result is ready, then returns it - only
    // callable once per future.
    int result = squareFuture.get();
    std::println("slowSquare(12) = {}", result);

    // --- std::promise/std::future: the manual, lower-level pair ---
    // A promise is the "write end" - one thread sets a value on it.
    // The future obtained from it is the "read end" - another thread reads
    // that value, blocking until it's set.
    std::promise<std::string> greetingPromise;
    std::future<std::string> greetingFuture = greetingPromise.get_future();

    std::jthread worker([&greetingPromise] {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        greetingPromise.set_value("Hello from the promise!");
    });

    std::println("");
    std::println("Waiting on greetingFuture...");
    std::println("{}", greetingFuture.get()); // blocks until set_value runs
    worker.join();

    // --- Propagating an exception through a future ---
    std::future<int> failingFuture = std::async(std::launch::async, [] () -> int {
        throw std::runtime_error("something went wrong on the worker thread");
    });

    std::println("");
    try {
        failingFuture.get(); // re-throws the same exception here, on this thread
    } catch (const std::exception& e) {
        std::println("Caught from future: {}", e.what());
    }

    return 0;
}
