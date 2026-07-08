// A mutex protects shared data, but doesn't help a thread wait efficiently
// for something to *become true* - checking a flag in a loop ("busy
// waiting") burns CPU the whole time it's waiting. A condition variable
// lets a thread sleep until another thread explicitly wakes it up.

#include <print>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>

int main() {

    std::mutex mtx;
    std::condition_variable cv;
    std::queue<int> items;
    bool finished{false};

    // The consumer waits for items to appear in the queue, one at a time,
    // until the producer signals there's nothing more coming.
    std::jthread consumer([&] {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);

            // cv.wait releases the lock while sleeping (so the producer can
            // acquire it) and reacquires it automatically before returning -
            // it only actually wakes up and proceeds once the predicate
            // (the lambda) is true, protecting against spurious wakeups.
            cv.wait(lock, [&] { return !items.empty() || finished; });

            if (!items.empty()) {
                int value = items.front();
                items.pop();
                lock.unlock(); // don't hold the lock while just printing
                std::println("Consumer got: {}", value);
            } else if (finished) {
                break;
            }
        }
        std::println("Consumer done.");
    });

    // The producer pushes a few items, waking the consumer after each one.
    std::jthread producer([&] {
        for (int i{1}; i <= 5; ++i) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                items.push(i);
                std::println("Producer made: {}", i);
            }
            cv.notify_one(); // wake the consumer up to go check the predicate
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            finished = true;
        }
        cv.notify_one(); // wake the consumer one last time so it can exit
    });

    producer.join();
    consumer.join();

    std::println("All done.");

    return 0;
}
