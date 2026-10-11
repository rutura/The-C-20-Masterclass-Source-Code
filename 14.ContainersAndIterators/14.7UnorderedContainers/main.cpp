#include <cstddef>
#include <functional>
#include <print>
#include <string>
#include <unordered_map>
#include <unordered_set>

// unordered_map / unordered_set: a HASH TABLE. The key is turned into a
// number (its hash), the number picks a bucket, and the element lives there.
// Find, insert and erase cost O(1) on average, and the order is unspecified.
//
//   hash("north") % buckets ──► bucket 3 ──► [north: 18.5]
//   hash("south") % buckets ──► bucket 0 ──► [south: 24.0] ─► [west: 16.0]   (a collision)
//   hash("east")  % buckets ──► bucket 5 ──► [east: 21.5]

// A key of your own needs two things: a hash, and operator== to settle collisions.
struct GridCell {
    int row;
    int column;
    bool operator==(const GridCell&) const = default;
};

template <>
struct std::hash<GridCell> {
    std::size_t operator()(const GridCell& cell) const noexcept {
        // Combine the two member hashes. Adding them would make (1,2) and (2,1)
        // collide, so one of them is scaled first.
        return std::hash<int>{}(cell.row) * 31 + std::hash<int>{}(cell.column);
    }
};

int main() {

    std::unordered_map<std::string, double> latest;
    latest["north"] = 18.5;
    latest["south"] = 24.0;
    latest.emplace("east", 21.5);
    latest.insert_or_assign("west", 16.0);

    std::println("--- the interface is the map's");
    std::println("north: {}   contains(moon): {}   size: {}", latest["north"], latest.contains("moon"), latest.size());

    // The order is whatever the table happens to hold. It can differ between
    // compilers and even between versions of the same library, so never rely on it.
    std::println("\n--- the order is unspecified");
    for (const auto& [station, temperature] : latest) {
        std::print("{}={} ", station, temperature);
    }
    std::println();

    // Look inside the table.
    std::println("\n--- buckets and load factor");
    std::unordered_map<int, int> numbers;
    std::size_t last_buckets{numbers.bucket_count()};
    int rehashes{0};
    for (int i{0}; i < 1'000; ++i) {
        numbers[i] = i;
        if (numbers.bucket_count() != last_buckets) {
            last_buckets = numbers.bucket_count();        // a REHASH: every element is re-placed
            ++rehashes;
        }
    }
    std::println("{} elements in {} buckets, load factor {:.2f}, max {:.2f}, {} rehashes on the way",
                 numbers.size(), numbers.bucket_count(), numbers.load_factor(),
                 numbers.max_load_factor(), rehashes);
    // When load_factor passes max_load_factor the table grows and rehashes.
    // That invalidates the iterators (14.4), though references to elements stay valid.
    // reserve(n) sizes the table up front, like vector::reserve.
    std::unordered_map<int, int> prepared;
    prepared.reserve(1'000);
    std::println("after reserve(1000): at least 1000 buckets? {}", prepared.bucket_count() >= 1'000);

    // A set of your own type, using the hash above.
    std::println("\n--- a custom key");
    std::unordered_set<GridCell> visited;
    visited.insert({1, 2});
    visited.insert({2, 1});
    visited.insert({1, 2});                                // already there
    std::println("{} distinct cells; (2,1) visited: {}; (3,3) visited: {}",
                 visited.size(), visited.contains({2, 1}), visited.contains({3, 3}));

    // map or unordered_map?
    //   need sorted iteration, range queries, or a key with only operator<  ->  map
    //   only lookups by exact key, many elements                            ->  unordered_map
    //   a bad hash (everything in one bucket) makes unordered_map O(n)
    return 0;
}
