#include <print>
#include <vector>

// An iterator (or pointer, or reference) into a container is only valid as
// long as the container does not rearrange itself. Operations that can move
// elements INVALIDATE them. Using an invalid iterator is undefined behaviour.

int main() {

    std::println("--- push_back may move the whole block");
    std::vector<double> readings{18.5, 19.0, 21.5};
    readings.reserve(3);                       // full: the next push_back must reallocate

    const double* first{readings.data()};      // a pointer into the old block
    auto it{readings.begin()};                 // an iterator into the old block

    readings.push_back(20.0);                  // reallocates: it and first now dangle

    std::println("the block moved: {}", first != readings.data());
    // std::println("{}", *it);                // undefined behaviour: reads freed memory
    it = readings.begin();                     // the fix: ask again after the change
    std::println("after asking again: {}", *it);

    // With reserve(), push_back does not reallocate, and iterators survive.
    // That is a guarantee only for the capacity you reserved, not a habit to rely on.

    std::println("\n--- erase inside a loop");
    std::vector<int> temperatures{12, -3, 18, -7, 21, -1, 15};

    // The tempting version:
    //     for (auto t{temperatures.begin()}; t != temperatures.end(); ++t) {
    //         if (*t < 0) temperatures.erase(t);      // t is invalid after erase, then ++t
    //     }
    // erase invalidates the iterator at and after the erased element.
    //
    // The right way: erase RETURNS an iterator to the next element, so use it,
    // and only step forward when nothing was erased.
    for (auto t{temperatures.begin()}; t != temperatures.end();) {
        if (*t < 0) {
            t = temperatures.erase(t);
        } else {
            ++t;
        }
    }
    for (int t : temperatures) {
        std::print("{} ", t);
    }
    std::println();

    // Chapter 15 shows the one-line version, std::erase_if.

    // What invalidates what, in short:
    // vector  push_back / insert / emplace: all, if it reallocates; otherwise from the change on
    //          erase: from the erased element on
    //          reserve: all, if it reallocates
    //          clear: all
    // deque    insert/erase in the middle: all; at the ends: iterators, but not references (14.5)
    // list     only the erased element itself (14.5)
    // map/set  only the erased element itself (14.6)
    // unordered containers  insert may rehash: iterators invalid, references stay (14.7)
    // The pattern: the more a container moves its elements, the more it invalidates.

    // A cheap safety net: the standard library of GCC and MSVC can check iterators for you in a Debug build:
    //   MSVC  Debug configuration (on by default; it opens the debug dialog)
    //   GCC   -D_GLIBCXX_DEBUG (aborts with a message)
    // and AddressSanitizer (9.12) reports the read of freed memory in either.
    // Uncomment the dereference above and try them.
    return 0;
}
