#include <coroutine>
#include <generator>
#include <print>
#include <ranges>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "scheduler.h"
#include "task.h"

/*
    Chapter 18 assignment - Coroutines

    Eight small jobs for the weather station, one for each idea of the chapter.
    task.h (Task<T>, 18.7) and scheduler.h (Scheduler, 18.9) are provided in
    this folder; the generator is std::generator.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Write each coroutine ABOVE main(), and the lines that use it under the
        exercise heading in main().

    A sensor reading that several exercises share: reading number n is
        15 + (n * 7) % 11          (as a double or an int, as the exercise says)
    so the readings for n = 1, 2, 3, ... are 22, 18, 25, 21, 17, 24, 20, 16, 23, 19, 15, 22, ...
*/

int main() {

    /*
        Exercise 1 - a generator (18.2, 18.3)

        Write   std::generator<int> hours(int first, int last, int step)
        that yields first, first + step, ... while the value is <= last.
        Print hours(0, 24, 6).

        Sample output:
            0 6 12 18 24
    */
    std::println("--- Exercise 1: a generator of hours ---");
    // TODO


    /*
        Exercise 2 - an endless generator and a pipeline (18.3)

        Write   std::generator<double> sensor()   that yields reading 1, 2, 3, ...
        forever (the formula is at the top). Then print the first five readings
        that are above 20, using std::views::filter and std::views::take on the
        generator.

        Sample output:
            22 25 21 24 23
    */
    std::println("\n--- Exercise 2: readings above 20 ---");
    // TODO


    /*
        Exercise 3 - a recursive generator (18.3)

        A tree of readings:   struct Branch { int value; std::vector<Branch> children; };
        Write   std::generator<int> all_values(const Branch& branch)   that yields the
        branch's own value first and then every value of its children, depth first
        (use std::ranges::elements_of for the children). Build this tree

                1
               / \
              2   3
             / \   \
            4   5   6

        print the values in order, and their sum.

        Sample output:
            1 2 4 5 3 6
            sum 21
    */
    std::println("\n--- Exercise 3: a tree of values ---");
    // TODO


    /*
        Exercise 4 - tasks that await tasks (18.7)

        Write   Task<int> reading(int n)   that prints "  reading #<n>" and returns the
        reading (as an int). Write   Task<double> mean_of_three()   that awaits readings
        1, 2 and 3 and returns their mean. Print it with two decimals, using .get().

        Sample output:
              reading #1
              reading #2
              reading #3
            mean 21.67
    */
    std::println("\n--- Exercise 4: awaiting three readings ---");
    // TODO


    /*
        Exercise 5 - an exception in a task (18.7)

        Write   Task<int> checked(int n)   that returns n * 10, but throws
        std::out_of_range{"no such sensor"} when n > 5. Write
        Task<int> safe_checked(int n)   that awaits checked(n) inside a try block
        and returns -1 if it throws. Print safe_checked(3) and safe_checked(9), then
        call checked(9).get() inside a try block in main() and print what() of
        the exception it throws.

        Sample output:
            safe_checked(3) = 30
            safe_checked(9) = -1
            caught: no such sensor
    */
    std::println("\n--- Exercise 5: an exception in a task ---");
    // TODO


    /*
        Exercise 6 - your own awaiter (18.6)

        Write a class Gate with a member wait() that returns an awaiter, and a member
        open(). A coroutine that does   co_await gate.wait();   pauses while the gate
        is closed (the awaiter keeps the handle) and goes straight through when it is
        already open (await_ready). open() opens the gate and resumes every
        coroutine that was waiting, in the order they arrived.

        Use it from   Task<void> visitor(Gate& gate, std::string name)   which prints
        "<name> waits at the gate", awaits the gate, then prints "<name> walks through".
        In main(): start "north" and "south" with .resume(), print "opening the gate",
        call open(), then start "east" with .resume().

        Sample output:
            north waits at the gate
            south waits at the gate
            opening the gate
            north walks through
            south walks through
            east waits at the gate
            east walks through
    */
    std::println("\n--- Exercise 6: a gate ---");
    // TODO


    /*
        Exercise 7 - the scheduler (18.9)

        Write   Task<void> worker(Scheduler& scheduler, std::string name, int steps)
        that, for n = 1..steps, adds reading n (the formula at the top) to a total,
        prints "<name> read #<n>", and then yields to the scheduler. When it is
        done it prints "<name> total <total>". Spawn "north" with 3 steps and "south"
        with 2 steps, and run the scheduler.

        Sample output:
            north read #1
            south read #1
            north read #2
            south read #2
            north read #3
            south total 40
            north total 65
    */
    std::println("\n--- Exercise 7: two workers ---");
    // TODO


    /*
        Exercise 8 - a lifetime bug (18.8)

        This coroutine is a trap:

            Task<void> greet(const std::string& name) {
                std::println("hello, {}", name);
                co_return;
            }

            Task<void> greeting{greet("a station name that is too long to hide inside the string object")};
            greeting.get();

        Build it (AddressSanitizer is already switched on in this folder's CMakeLists.txt), watch it fail,
        and then write the FIXED version below: same call, no sanitizer report. Explain
        in a comment why the original reads freed memory, and why a Task makes it
        worse than a normal function.

        Sample output (of the fixed version):
            hello, a station name that is too long to hide inside the string object
    */
    std::println("\n--- Exercise 8: fix the lifetime bug ---");
    // TODO

    return 0;
}
