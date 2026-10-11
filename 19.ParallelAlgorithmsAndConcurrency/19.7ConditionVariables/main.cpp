#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>
#include <print>
#include <stop_token>
#include <thread>
#include <utility>
#include <vector>

// A mutex answers "who may touch this data now?". It does not answer "how do
// I wait until there is something to touch?". A consumer that finds the queue
// empty could loop and look again (spinning, burning a whole core for nothing),
// or sleep for a while and hope (late, and wasteful). A CONDITION VARIABLE
// is the right tool: the thread goes to sleep and the thread that changes
// things wakes it.
//
//     std::unique_lock lock{mutex};
//     cv.wait(lock, [&] { return there_is_something; });   sleep until the condition is true
//     ...use the data, still holding the lock...
//
// and in the thread that changes the state:
//
//     { std::lock_guard lock{mutex}; make_something_true(); }
//     cv.notify_one();                                       wake one sleeper
//
// wait() does three things in one indivisible step: it checks the condition,
// and if it is false it UNLOCKS the mutex and sleeps; when woken it locks the
// mutex again and re-checks. That is why it needs a std::unique_lock (which can
// unlock and lock again; a lock_guard cannot). The re-check is not optional:
// a thread can wake up when nothing happened (a spurious wakeup), or find that
// another thread took the item first. Always pass the condition to wait().

// ---- A queue between threads ------------------------------------------------------------------
// push() waits while the queue is full, pop() waits while it is empty. The
// queue is BOUNDED, which matters: if producers are faster than consumers, an
// unbounded queue grows until memory runs out.
//
// The lambdas below say [this]: a lambda inside a member function may use the
// object's members only if it captures the object, and [this] does that.
template <typename T>
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) : capacity_{capacity} {}

    void push(T item) {
        std::unique_lock<std::mutex> lock{mutex_};
        not_full_.wait(lock, [this] { return items_.size() < capacity_; });
        items_.push_back(std::move(item));
        if (items_.size() > largest_backlog_) {
            largest_backlog_ = items_.size();
        }
        not_empty_.notify_one();
    }

    // Returns std::nullopt when the queue is closed AND empty: "no more items, ever".
    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock{mutex_};
        not_empty_.wait(lock, [this] { return !items_.empty() || closed_; });
        if (items_.empty()) {
            return std::nullopt;
        }
        T item{std::move(items_.front())};
        items_.pop_front();
        not_full_.notify_one();
        return item;
    }

    // The producers are finished. Wakes EVERY sleeping consumer so that each
    // one can see "closed" and leave: notify_one would wake only one.
    void close() {
        {
            std::lock_guard<std::mutex> lock{mutex_};
            closed_ = true;
        }
        not_empty_.notify_all();
    }

    std::size_t largest_backlog() const {
        std::lock_guard<std::mutex> lock{mutex_};
        return largest_backlog_;
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::deque<T> items_;
    std::size_t capacity_;
    std::size_t largest_backlog_{0};
    bool closed_{false};
};

int main() {
    // ---- 1. Producers and consumers --------------------------------------------------------
    // Two stations produce 1,000 readings each, two analysts consume them. The
    // queue holds at most 8, so the fast side has to wait for the slow side.
    std::println("--- producers and consumers");
    constexpr std::size_t capacity{8};
    BoundedQueue<int> queue{capacity};

    std::vector<long long> consumer_sum(2, 0);
    std::vector<int> consumer_count(2, 0);
    {
        std::vector<std::jthread> consumers;
        for (std::size_t c{0}; c < consumer_sum.size(); ++c) {
            consumers.emplace_back([&queue, &consumer_sum, &consumer_count, c] {
                while (std::optional<int> reading{queue.pop()}) {
                    consumer_sum[c] += *reading;
                    ++consumer_count[c];
                }
            });
        }

        {
            std::vector<std::jthread> producers;
            for (int station{0}; station < 2; ++station) {
                producers.emplace_back([&queue, station] {
                    for (int i{0}; i < 1'000; ++i) {
                        queue.push(station * 1'000 + i);
                    }
                });
            }
        }   // the producers are joined here: everything has been pushed

        queue.close();
    }       // the consumers are joined here: they have drained the queue and left

    std::println("consumed {} readings, sum {}", consumer_count[0] + consumer_count[1], consumer_sum[0] + consumer_sum[1]);
    std::println("the queue never held more than {}: {}", capacity, queue.largest_backlog() <= capacity);
    std::println("[varies] the two consumers took {} and {} readings", consumer_count[0], consumer_count[1]);

    // ---- 2. Waking a sleeper that will never get its item ---------------------------------------
    // What if the thing it waits for never happens? close() above is one way
    // out. A std::stop_token (19.3) is another: with std::condition_variable_any,
    // wait() accepts a token, and request_stop() wakes the sleeper.
    std::println("\n--- stop a waiting thread");
    std::mutex mutex;
    std::condition_variable_any wakeup;
    bool news_arrived{false};
    {
        std::jthread waiter{[&](std::stop_token token) {
            std::unique_lock<std::mutex> lock{mutex};
            bool condition_true{wakeup.wait(lock, token, [&] { return news_arrived; })};
            std::println("the waiter woke up; the news arrived: {}", condition_true);
        }};
        std::this_thread::sleep_for(std::chrono::milliseconds{20});
        waiter.request_stop();
    }

    // Mistakes to avoid:
    //   - calling wait() WITHOUT a condition: a notify that comes before the
    //     wait is lost, and the thread sleeps for ever (the "lost wakeup")
    //   - changing the condition without holding the mutex: the sleeper can
    //     check it, miss the change, and go to sleep after the notify
    //   - using notify_one when several threads must react (use notify_all)
    return 0;
}
