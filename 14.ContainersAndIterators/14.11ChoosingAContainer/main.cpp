#include <algorithm>
#include <chrono>
#include <cstddef>
#include <map>
#include <print>
#include <random>
#include <set>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// "Which container?" is best answered by measuring on your own data. This
// program measures one common question, LOOKUP BY KEY, on 100'000 keys.
// Build with optimization (Release, or -O2): timings of an unoptimized build
// say little. The numbers are for orientation, and differ on every machine.

using Clock = std::chrono::steady_clock;

template <typename Work>
double milliseconds(Work&& work) {
    auto start{Clock::now()};
    work();
    return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

void report(std::string_view name, double build_ms, double lookup_ms, std::size_t queries, std::size_t hits) {
    std::println("{:<22} build {:8.2f} ms   {:8.1f} ns per lookup   ({} hits)",
                 name, build_ms, lookup_ms * 1'000'000.0 / static_cast<double>(queries), hits);
}

int main() {
    constexpr int count{100'000};

    // Even numbers 0, 2, 4, ... in random order. A lookup of an odd number
    // is a miss, so about half of the queries find something.
    std::vector<int> keys;
    keys.reserve(count);
    for (int i{0}; i < count; ++i) {
        keys.push_back(i * 2);
    }
    std::mt19937 engine{12345};                       // a fixed seed: the same data every run
    std::ranges::shuffle(keys, engine);

    std::vector<int> queries;
    queries.reserve(200'000);
    for (int i{0}; i < 200'000; ++i) {
        queries.push_back(static_cast<int>(engine() % (2 * count)));
    }
    // The plain vector is O(n) per lookup, so it gets fewer queries to stay quick.
    const std::vector<int> few_queries{queries.begin(), queries.begin() + 500};

    std::println("{} keys, {} queries (the vector scan: {})\n", count, queries.size(), few_queries.size());

    {   // vector, searched from the start: O(n)
        std::vector<int> v;
        double build{milliseconds([&] { v = keys; })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : few_queries) {
                hits += std::ranges::find(v, q) != v.end();
            }
        })};
        report("vector, linear find", build, lookup, few_queries.size(), hits);
    }
    {   // vector sorted once, then binary search: O(log n)
        std::vector<int> v;
        double build{milliseconds([&] { v = keys; std::ranges::sort(v); })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : queries) {
                hits += std::ranges::binary_search(v, q);
            }
        })};
        report("sorted vector", build, lookup, queries.size(), hits);
    }
    {   // set: a tree, O(log n), one allocation per element
        std::set<int> s;
        double build{milliseconds([&] { s.insert(keys.begin(), keys.end()); })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : queries) {
                hits += s.contains(q);
            }
        })};
        report("std::set", build, lookup, queries.size(), hits);
    }
    {   // map: the same tree, with a value attached
        std::map<int, int> m;
        double build{milliseconds([&] { for (int k : keys) { m[k] = k; } })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : queries) {
                hits += m.contains(q);
            }
        })};
        report("std::map", build, lookup, queries.size(), hits);
    }
    {   // unordered_set: a hash table, O(1) on average
        std::unordered_set<int> s;
        double build{milliseconds([&] { s.insert(keys.begin(), keys.end()); })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : queries) {
                hits += s.contains(q);
            }
        })};
        report("std::unordered_set", build, lookup, queries.size(), hits);
    }
    {   // the same, told the size up front
        std::unordered_set<int> s;
        double build{milliseconds([&] { s.reserve(keys.size()); s.insert(keys.begin(), keys.end()); })};
        std::size_t hits{0};
        double lookup{milliseconds([&] {
            for (int q : queries) {
                hits += s.contains(q);
            }
        })};
        report("unordered_set+reserve", build, lookup, queries.size(), hits);
    }

    // A rough guide, from the numbers above and from this chapter:
    //
    //   a sequence you walk through, add to at the back        vector (the default)
    //   adds and removes at both ends                          deque
    //   stable positions, splicing, insert in the middle       list (rarely)
    //   find by key, in order, ranges of keys                  map / set
    //   find by exact key, no order                            unordered_map / unordered_set
    //   built once, searched many times                        sorted vector (or flat_map)
    //   largest or smallest first                              priority_queue
    //
    // When unsure, start with vector and measure before you change.
    return 0;
}
