#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <execution>
#include <functional>
#include <future>
#include <mutex>
#include <numeric>
#include <print>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "thread_pool.h"

/*
    Chapter 19 assignment - Parallel Algorithms and Concurrency

    Eight small jobs for the weather network. thread_pool.h (19.10) is provided
    in this folder.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Write each helper (function or class) ABOVE main(), and the lines that
        use it under the exercise heading in main().
      - Every thread must be joined: use std::jthread, or join() yourself.
      - Keep the output deterministic: print results from main(), after the
        threads have finished, never from inside the threads.

    When an exercise gives you a wrong number, it is a race. Build the
    program with ThreadSanitizer to find it (19.12, GCC or Clang on Linux):
        cmake -S . -B build -G Ninja -DCMAKE_CXX_FLAGS="-fsanitize=thread -g"
    (std::execution::par reports false races from inside oneTBB; ignore those
    or suppress them with  TSAN_OPTIONS=suppressions=file  containing  race:tbb::)
*/

int main() {

    /*
        Exercise 1 - parallel algorithms (19.2)

        Make a vector<int> `celsius` of 1,000,000 values: celsius[i] = i % 40.
        With std::transform and std::execution::par, convert every value to
        Fahrenheit (c * 9.0 / 5.0 + 32.0) into a vector<double>. Print the first
        five. With std::count_if (par) count how many are above 86 F.
        Then fill a vector<long long> with 1..1,000,000 and add it up with
        std::reduce (par).

        Sample output:
            first five: 32 33.8 35.6 37.4 39.2
            hotter than 86 F: 225000
            sum: 500000500000
    */
    std::println("--- Exercise 1: parallel algorithms ---");
    // TODO


    /*
        Exercise 2 - threads and results (19.3)

        Fill a vector<long long> with 1..2,000. Start four std::jthread. Thread t
        adds up the 500 numbers from index t * 500, and stores its answer in
        slot t of a vector<long long> `partial` (sized BEFORE the threads start:
        no two threads write the same element). Print each partial sum and the
        total.

        Sample output:
            thread 0: 125250
            thread 1: 375250
            thread 2: 625250
            thread 3: 875250
            total: 2001000
    */
    std::println("\n--- Exercise 2: four threads, four slices ---");
    // TODO


    /*
        Exercise 3 - a shared counter (19.4, 19.5, 19.6)

        Four stations each count 250,000 readings in ONE shared counter. Do it
        twice: with an int protected by a std::mutex (lock_guard), and with a
        std::atomic<int>. (First try it with no protection and see the wrong
        number, then fix it.)

        Sample output:
            with a mutex: 1000000
            with an atomic: 1000000
    */
    std::println("\n--- Exercise 3: a shared counter ---");
    // TODO


    /*
        Exercise 4 - a thread-safe class (19.5)

        Write class StationLog that owns a std::vector<std::string> of notes and
        a mutable std::mutex. Members: add(std::string note), count(), and
        longest() (the length of the longest note). Every member locks. Four
        threads each add 100 notes of the form  "station <S> note <I>".

        Sample output:
            400 notes, the longest has 17 characters
    */
    std::println("\n--- Exercise 4: a thread-safe log ---");
    // TODO


    /*
        Exercise 5 - locking several mutexes (19.5)

        struct Account { std::mutex mutex; int battery{100}; };
        Write transfer(Account& from, Account& to, int amount) that moves battery
        between two accounts, taking BOTH mutexes with std::scoped_lock.
        Three accounts (north, south, east) and three threads in a ring:
        one moves 1 unit north -> south, 1,000 times, the next south -> east,
        the third east -> north. Without scoped_lock this can deadlock.

        Sample output:
            north 100, south 100, east 100
            total 300
    */
    std::println("\n--- Exercise 5: a ring of transfers ---");
    // TODO


    /*
        Exercise 6 - a condition variable (19.7)

        Write class Mailbox with ONE slot: put(int) waits while the slot is full,
        take() waits while it is empty. Use a mutex, a condition_variable, and a
        predicate in every wait(). A producer thread puts 1..10, a consumer
        thread takes ten times and adds up what it got.

        Sample output:
            received sum: 55
    */
    std::println("\n--- Exercise 6: a mailbox ---");
    // TODO


    /*
        Exercise 7 - futures (19.8)

        Write  double mean_of(const std::vector<double>& values, std::size_t first,
        std::size_t last)  that throws std::invalid_argument{"empty slice"} when
        first == last. With values 1..1000, start one std::async
        (std::launch::async) per slice {0,250}, {250,500}, {500,500}, {500,1000}.
        Then get() the futures in order, catching the exception.

        Sample output:
            slice 0: mean 125.5
            slice 1: mean 375.5
            slice 2: empty slice
            slice 3: mean 750.5
    */
    std::println("\n--- Exercise 7: futures and an exception ---");
    // TODO


    /*
        Exercise 8 - the thread pool (19.10)

        With a ThreadPool of 4 workers, submit ten jobs. Job p adds up the
        squares of the numbers from p * 100 + 1 to (p + 1) * 100 and returns
        the total as a long long. Collect the futures, add the ten answers.

        Sample output:
            sum of squares 1..1000: 333833500
    */
    std::println("\n--- Exercise 8: a thread pool ---");
    // TODO

    return 0;
}
