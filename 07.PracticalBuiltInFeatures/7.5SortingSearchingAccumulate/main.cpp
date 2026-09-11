#include <print>
#include <array>
#include <algorithm>   // ranges::sort, ranges::binary_search
#include <numeric>     // accumulate
#include <string>

int multiply(int x, int y) {
    return x * y;
}

int main() {
    using namespace std::string_literals;

    // 6.3 already introduced ranges::sort in passing; here it earns its
    // place - a real search needs sorted data first.
    std::array fruits{"mango"s, "kiwi"s, "fig"s, "date"s, "apple"s};

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

    // binary_search only works correctly on already-sorted data - that is
    // the trade a sort buys you: O(log n) lookups instead of O(n). fruits
    // is currently sorted DESCENDING from the std::ranges::greater call
    // above; binary_search assumes ascending order by default, so sort it
    // back first - searching with the wrong ordering assumption is exactly
    // how binary_search gives wrong answers on "sorted" data.
    std::ranges::sort(fruits);

    bool found{std::ranges::binary_search(fruits, "kiwi"s)};
    std::println("\n\n\"kiwi\" {} found in fruits", found ? "was" : "was not");

    found = std::ranges::binary_search(fruits, "guava"s);
    std::println("\"guava\" {} found in fruits", found ? "was" : "was not");

    // std::accumulate folds a range down to a single value. With no extra
    // argument the fold operation is +, so this sums the elements.
    // std::accumulate has no range counterpart, so we pass begin() and end() explicitly.
    constexpr std::array quantities{10, 20, 30, 40};
    std::println("\nTotal of quantities: {}",
                  std::accumulate(quantities.begin(), quantities.end(), 0));

    // Passing a binary operation changes what "combine" means. A named
    // function...
    constexpr std::array factors{1, 2, 3, 4, 5};
    std::println("Product of factors (named function): {}",
                  std::accumulate(factors.begin(), factors.end(), 1, multiply));

    // ...or a lambda works the same way, without a separate declaration.
    std::println("Product of factors (lambda): {}",
                  std::accumulate(factors.begin(), factors.end(), 1,
                                   [](int x, int y) { return x * y; }));

    // simulate the default: a lambda that adds 
    std::println("Total of quantities (lambda, reproducing the default): {}",
                  std::accumulate(quantities.begin(), quantities.end(), 0,
                                   [](int x, int y) { return x + y; }));

    // Can even use a built in binary function for addiion 
    std::println("Total of quantities (std::plus): {}",
                  std::accumulate(quantities.begin(), quantities.end(), 0, std::plus<int>()));

    return 0;
}
