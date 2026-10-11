#include <algorithm>
#include <atomic>
#include <barrier>
#include <chrono>
#include <cstddef>
#include <latch>
#include <numeric>
#include <print>
#include <semaphore>
#include <thread>
#include <vector>

// C++20 added three small tools for the situations that mutexes and condition
// variables handle awkwardly: "everybody wait until we are all here", "do this
// in rounds", and "no more than N at a time".
//
//     std::latch       a countdown that can be used ONCE: threads count it down, others wait for zero
//     std::barrier     a meeting point that can be used again and again, one round after another
//     std::counting_semaphore<N>   N tickets: acquire() takes one (waiting if none is left), release() gives it back

constexpr std::size_t station_count{4};

int main() {
    // ---- 1. A latch as a starting gun, and as a finish line ---------------------------------
    std::println("--- latch");
    std::latch start_gun{1};                       // opened by main
    std::latch finish_line{static_cast<std::ptrdiff_t>(station_count)};   // opened by the stations
    std::vector<int> results(station_count, 0);
    {
        std::vector<std::jthread> stations;
        for (std::size_t id{0}; id < station_count; ++id) {
            stations.emplace_back([&, id] {
                start_gun.wait();                  // nobody starts before main says so
                results[id] = static_cast<int>(id * id);
                finish_line.count_down();          // "I am done"
            });
        }
        // The stations are all created and waiting. Go.
        start_gun.count_down();
        finish_line.wait();                        // returns when the count has reached zero
        std::println("all stations finished, results {} {} {} {}", results[0], results[1], results[2], results[3]);
    }

    // ---- 2. A barrier: work in rounds -------------------------------------------------------------
    // Every round, each station computes one number. Nobody may start round 2
    // before everybody finished round 1, because round 2 uses all the numbers
    // of round 1. arrive_and_wait() is the meeting point. When the LAST thread
    // arrives, the barrier runs its completion function once (on that thread),
    // then releases everybody into the next round.
    std::println("\n--- barrier");
    std::vector<int> slot(station_count, 0);
    int round_number{0};
    auto end_of_round{[&slot, &round_number]() noexcept {
        std::println("round {} complete, total {}", ++round_number, std::accumulate(slot.begin(), slot.end(), 0));
    }};
    std::barrier meeting{static_cast<std::ptrdiff_t>(station_count), end_of_round};
    {
        std::vector<std::jthread> stations;
        for (std::size_t id{0}; id < station_count; ++id) {
            stations.emplace_back([&slot, &meeting, id] {
                for (int round{1}; round <= 3; ++round) {
                    slot[id] = static_cast<int>(id) * 10 + round;
                    meeting.arrive_and_wait();     // wait for the others, then the completion function runs
                }
            });
        }
    }

    // ---- 3. A semaphore: at most two at a time -------------------------------------------------------
    // The weather service lets us have only two connections open. Six
    // stations want to upload. Each one takes a ticket first.
    std::println("\n--- semaphore");
    std::counting_semaphore<4> connections{2};     // 4 is the largest count this type can hold; we start with 2
    std::atomic<int> open_now{0};
    std::atomic<int> most_open{0};
    {
        std::vector<std::jthread> uploads;
        for (int i{0}; i < 6; ++i) {
            uploads.emplace_back([&] {
                connections.acquire();             // waits while both tickets are in use
                int now{++open_now};
                int seen{most_open.load()};
                while (now > seen && !most_open.compare_exchange_weak(seen, now)) {
                }
                std::this_thread::sleep_for(std::chrono::milliseconds{20});
                --open_now;
                connections.release();
            });
        }
    }
    std::println("never more than 2 connections open at once: {}", most_open.load() <= 2);
    std::println("[varies] the most that were open together: {}", most_open.load());

    // Which one when?
    //   latch      one-time gate or countdown ("wait for all the workers")
    //   barrier    the same gate again and again ("end of each round")
    //   semaphore  limit how many threads may be inside at once
    //   mutex      exactly one at a time, and protects data
    return 0;
}
