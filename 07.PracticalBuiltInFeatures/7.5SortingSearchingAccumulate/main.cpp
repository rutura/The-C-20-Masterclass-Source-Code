#include <print>
#include <string>
#include <array>
#include <algorithm>


int main(){

    using namespace std::string_literals;

    // 6.3 already introduced ranges::sort in passing; here it earns its
    // place - a real search needs sorted data first.
    std::array fruits{ "mango"s, "kiwi"s, "fig"s, "date"s, "apple"s };
    
    std::print("Unsorted: ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }

    std::ranges::sort(fruits);

    std::print("\nSorted:   ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // sort's "ascending order" is not magic either - it is a default
    // comparator, std::ranges::less, doing the comparing. Passing it
    // explicitly reproduces the exact same order as the call above.
    std::ranges::sort(fruits, std::ranges::less{});

    std::print("\nSorted (explicit std::ranges::less): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // Swap in std::ranges::greater instead and the same algorithm sorts
    // descending - sort's job never changes, only the rule it compares
    // consecutive elements with does.
    std::ranges::sort(fruits, std::ranges::greater{});

    std::print("\nSorted descending (std::ranges::greater): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // A lambda can reproduce std::ranges::less by hand too - same
    // two-argument, bool-returning shape accumulate's combine function
    // had, just used differently: true means "a belongs before b".
    std::ranges::sort(fruits,
        [](const std::string& a, const std::string& b) {
            return a < b;
    });


    std::print("\nSorted ascending (lambda, reproducing std::ranges::less): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // Flip the comparison and the lambda reproduces std::ranges::greater
    // instead - same idea as the built-in, spelled out.
    std::ranges::sort(fruits,
        [](const std::string& a, const std::string& b) {
            return a > b;
    });


    std::print("\nSorted descending (lambda, reproducing std::ranges::greater): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // A lambda comparator can also express a rule std::ranges::less/greater
    // cannot - here, "shorter name first" instead of alphabetical order.
    // Same two-argument, bool-returning shape as accumulate's combine
    // function; sort just uses the return value differently (true means
    // "the first argument belongs before the second").
    std::ranges::sort(fruits,
        [](const std::string& a, const std::string& b) {
            if (a.size() != b.size()) {
                return a.size() < b.size();   // shorter name first
            }
            return a < b;                     // same length: alphabetical
    });

    std::print("\nSorted by length, ascending (lambda): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }


    // Flip the comparison and the same lambda shape sorts the opposite
    // way - longest name first.
    std::ranges::sort(fruits,
        [](const std::string& a, const std::string& b) {
            if (a.size() != b.size()) {
                return a.size() > b.size();   // longer name first
            }
            return a < b;                     // same length: alphabetical
   });

    std::print("\nSorted by length, descending (lambda): ");
    for (const std::string& fruit : fruits) {
        std::print("{} ", fruit);
    }



}