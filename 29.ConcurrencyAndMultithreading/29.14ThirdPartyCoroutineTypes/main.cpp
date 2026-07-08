// The generator<T> from the last lecture works, but calling it like a
// function - task3() - isn't how C++ programmers normally consume a
// sequence; a range-based for loop is. unique_generator (in
// unique_generator.h, adapted from a real-world reference implementation -
// see the attribution comment at the top of that file) adds proper
// begin()/end() iterators on top of the same coroutine machinery, so a
// generator can be used exactly like any other range.

#include <print>
#include <coroutine>
#include <cassert>
#include "unique_generator.h"

unique_generator<int> generate_numbers() {
    std::println("generate_numbers starting");
    co_yield 10;
    std::println("After stop point #1");

    co_yield 20;
    std::println("After stop point #2");

    co_yield 30;
    std::println("After stop point #3");
    std::println("generate_numbers ending");
}

unique_generator<int> infinite_number_stream(int start = 0) {
    auto value = start;
    for (int i = 0; ; ++i) {
        co_yield value;
        ++value;
    }
}

unique_generator<int> range(int first, int last) {
    while (first != last) {
        co_yield first++;
    }
}

int main() {

    // Creating a coroutine only sets it up - initial_suspend() means
    // nothing inside generate_numbers() has run yet, so nothing prints
    // unless task1 is actually driven, e.g. by uncommenting the loop
    // below (which uses the begin()/end() iterators this lecture adds).
    auto task1 = generate_numbers();
    /*
    for (auto i = task1.begin(); i != task1.end(); ++i) {
        std::println("value : {}", *i);
    }
    */

    // infinite_number_stream() never returns - safe to iterate here only
    // because a generator produces one value per resume, on demand;
    // uncomment cautiously, since this loop truly never stops on its own.
    /*
    auto task2 = infinite_number_stream();
    for (std::size_t i{}; ; ++i) {
        std::println("value : {}", task2());
    }
    */

    // range() is what this lecture actually runs - and now with a plain
    // range-based for loop instead of the manual task3() calls the last
    // lecture needed, since unique_generator supplies real iterators.
    auto task3 = range(0, 25);
    for (auto v : task3) {
        std::println("value : {}", v);
    }

    std::println("Done!");

    return 0;
}
