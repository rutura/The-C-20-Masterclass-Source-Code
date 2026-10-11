#include <functional>
#include <map>
#include <print>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// map and set keep their elements SORTED by key, in a balanced tree.
// Find, insert and erase cost O(log n) (7.5), and iteration comes out in order.

int main() {

    // A map holds key -> value pairs. Keys are unique.
    std::map<std::string, double> latest;
    latest["north"] = 18.5;                   // operator[] creates the entry if needed
    latest["south"] = 24.0;
    latest.insert({"east", 21.5});            // insert does NOT replace an existing key
    latest.insert({"east", 99.0});            // ignored: east is already there
    latest.insert_or_assign("south", 25.5);   // this one replaces
    latest.emplace("west", 16.0);

    // Iterating gives pairs in key order. A structured binding (10.11) names the halves.
    std::println("--- sorted by key");
    for (const auto& [station, temperature] : latest) {
        std::println("{:<6} {:5.1f}", station, temperature);
    }

    // The trap of operator[]: READING a missing key creates it.
    std::println("\n--- operator[] versus find versus at");
    std::println("size before: {}", latest.size());
    if (latest["centre"] > 20.0) {            // looks like a question, is an insert
        std::println("warm");
    }
    std::println("size after asking about 'centre': {}", latest.size());

    // find returns an iterator, end() when missing. contains (C++20) just says yes or no.
    if (auto it{latest.find("east")}; it != latest.end()) {
        std::println("find: east is {}", it->second);   // it->first is the key, it->second the value
    }
    std::println("contains(\"moon\"): {}", latest.contains("moon"));

    // at() throws instead of inserting (13.4).
    try {
        std::println("{}", latest.at("moon"));
    }
    catch (const std::out_of_range&) {
        std::println("at(\"moon\") threw out_of_range");
    }

    // The key is const inside the map: changing it would break the ordering.
    // it->first = "x";                       // error

    // The classic use: counting.
    std::println("\n--- counting with operator[]");
    std::vector<std::string> log{"north", "east", "north", "west", "north", "east"};
    std::map<std::string, int> readings_per_station;
    for (const auto& station : log) {
        ++readings_per_station[station];      // a missing key starts at 0, which is what we want
    }
    for (const auto& [station, count] : readings_per_station) {
        std::println("{:<6} {}", station, count);
    }

    // Ordered means range queries are cheap.
    std::println("\n--- lower_bound and upper_bound");
    auto from{latest.lower_bound("d")};       // first key not less than "d"
    auto to{latest.upper_bound("o")};         // first key greater than "o"
    for (auto it{from}; it != to; ++it) {
        std::print("{} ", it->first);
    }
    std::println("  (keys from d to o)");

    latest.erase("centre");
    std::println("erased centre, size {}", latest.size());

    // set: just keys. Duplicates disappear, the rest comes out sorted.
    std::println("\n--- set");
    std::set<int> hours{14, 9, 14, 3, 9, 22};
    for (int h : hours) {
        std::print("{} ", h);
    }
    std::println("  ({} distinct)", hours.size());
    auto [position, inserted]{hours.insert(9)};    // insert tells you whether it was new
    std::println("insert(9): new? {}, already at {}", inserted, *position);

    // A different ordering is a template argument. std::greater sorts descending.
    std::set<int, std::greater<>> descending{hours.begin(), hours.end()};
    std::print("descending: ");
    for (int h : descending) {
        std::print("{} ", h);
    }
    std::println();

    // multimap and multiset allow repeated keys.
    std::println("\n--- multimap: several values per key");
    std::multimap<std::string, double> by_station;
    by_station.emplace("north", 18.5);
    by_station.emplace("north", 19.0);
    by_station.emplace("south", 24.0);
    by_station.emplace("north", 17.5);
    auto [first, last]{by_station.equal_range("north")};
    std::print("north: ");
    for (auto it{first}; it != last; ++it) {
        std::print("{} ", it->second);
    }
    std::println("  ({} readings)", by_station.count("north"));
    return 0;
}
