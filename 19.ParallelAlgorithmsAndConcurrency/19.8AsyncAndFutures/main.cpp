#include <chrono>
#include <cstddef>
#include <functional>
#include <future>
#include <numeric>
#include <print>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

// In 19.3 a thread could not return a value: we wrote into a variable and read
// it after join(). That works, but it is clumsy, and an exception in the
// thread ends the program. <future> adds a better way to get a result back:
//
//     std::future<T>     a ticket for a T that will exist LATER
//     future.get()       waits until it is ready, then gives the value
//                        (or throws the exception the work threw)
//
// The other end of the ticket, where the value is put in, comes in three
// forms: std::async (runs a function for you), std::promise (you set the
// value yourself) and std::packaged_task (wraps a callable, runs it when
// you say).

double sum_of(const std::vector<double>& values, std::size_t first, std::size_t last) {
    return std::accumulate(values.begin() + static_cast<std::ptrdiff_t>(first),
                           values.begin() + static_cast<std::ptrdiff_t>(last), 0.0);
}

// A pretend network call.
int fetch_reading(int station) {
    std::this_thread::sleep_for(std::chrono::milliseconds{100});
    if (station < 0) {
        throw std::invalid_argument{"no such station"};
    }
    return 20 + station;
}

template <typename Work>
double milliseconds(Work&& work) {
    auto started{std::chrono::steady_clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count();
}

int main() {
    // ---- 1. std::async: a function call that runs somewhere else ---------------------------------
    // The first argument says WHERE. std::launch::async: on a new thread, now.
    // The rest is the callable and its arguments, copied like a thread's (19.3).
    std::println("--- async and get");
    std::vector<double> readings(1'000);
    std::iota(readings.begin(), readings.end(), 1.0);

    std::future<double> first_half{std::async(std::launch::async, sum_of, std::cref(readings), 0, 500)};
    std::future<double> second_half{std::async(std::launch::async, sum_of, std::cref(readings), 500, 1'000)};
    // main is free to do other work here; get() waits only if the answer is not ready yet.
    std::println("halves: {} + {}", first_half.get(), second_half.get());
    // A future gives its value ONCE: calling get() again is an error.

    // ---- 2. Where does it run? ------------------------------------------------------------------------
    std::println("\n--- async or deferred");
    std::thread::id main_id{std::this_thread::get_id()};
    std::future<std::thread::id> on_thread{std::async(std::launch::async, [] { return std::this_thread::get_id(); })};
    std::future<std::thread::id> lazily{std::async(std::launch::deferred, [] { return std::this_thread::get_id(); })};
    std::println("launch::async ran on another thread: {}", on_thread.get() != main_id);
    std::println("launch::deferred ran on main, at get(): {}", lazily.get() == main_id);
    // Without a policy, std::async(f) may choose EITHER. Always say which.

    // ---- 3. The future of an async blocks when it is destroyed -------------------------------------------
    // A future that came from std::async waits for its work in its destructor.
    // So "fire and forget" does not exist: if you throw the future away, the
    // statement does not finish until the work does, and two such calls run one after the other.
    std::println("\n--- throwing the future away");
    double discarded_ms{milliseconds([] {
        static_cast<void>(std::async(std::launch::async, fetch_reading, 1));   // the temporary future is destroyed at once: waits 100 ms
        static_cast<void>(std::async(std::launch::async, fetch_reading, 2));   // and then another 100 ms
    })};
    double kept_ms{milliseconds([] {
        auto a{std::async(std::launch::async, fetch_reading, 1)};
        auto b{std::async(std::launch::async, fetch_reading, 2)};
        a.get();
        b.get();
    })};
    std::println("[varies] futures discarded: {:.0f} ms, futures kept: {:.0f} ms", discarded_ms, kept_ms);
    std::println("[varies] keeping the futures lets the two calls overlap: {}", kept_ms < discarded_ms * 0.75);

    // ---- 4. Exceptions come out of get() --------------------------------------------------------------------
    std::println("\n--- an exception through a future");
    std::future<int> broken{std::async(std::launch::async, fetch_reading, -1)};
    try {
        broken.get();
    }
    catch (const std::exception& error) {
        std::println("get() threw: {}", error.what());
    }

    // ---- 5. std::promise: set the value yourself ------------------------------------------------------------------
    // A promise is the writing end, a future the reading end of the same slot.
    // Use it when the value comes from something that is not a function call.
    std::println("\n--- promise and future");
    std::promise<int> forecast_promise;
    std::future<int> forecast{forecast_promise.get_future()};
    std::jthread forecaster{[&forecast_promise] {
        std::this_thread::sleep_for(std::chrono::milliseconds{20});
        forecast_promise.set_value(27);                         // or set_exception(std::current_exception())
    }};
    std::println("tomorrow: {} C", forecast.get());
    forecaster.join();

    // ---- 6. std::packaged_task: a callable that remembers its future ------------------------------------------
    // It does not run by itself: you call it, on whichever thread you like.
    // That is the missing piece for a thread pool (19.10).
    std::println("\n--- packaged_task");
    std::packaged_task<int(int)> job{fetch_reading};
    std::future<int> job_result{job.get_future()};
    std::println("the job has not run yet; the result is ready: {}",
                 job_result.wait_for(std::chrono::milliseconds{0}) == std::future_status::ready);
    std::thread worker{std::move(job), 5};                      // a packaged_task is move-only
    worker.join();
    // (Two separate statements: the order in which the arguments of a call are
    // evaluated is not specified, and get() empties the future.)
    bool ready_now{job_result.wait_for(std::chrono::milliseconds{0}) == std::future_status::ready};
    int value{job_result.get()};
    std::println("after running: ready {}, value {}", ready_now, value);

    // ---- 7. Waiting with a limit ---------------------------------------------------------------------------------
    std::println("\n--- waiting with a limit");
    std::future<int> slow{std::async(std::launch::async, fetch_reading, 3)};
    if (slow.wait_for(std::chrono::milliseconds{10}) == std::future_status::timeout) {
        std::println("not ready after 10 ms, doing something else");
    }
    std::println("then: {}", slow.get());

    return 0;
}
