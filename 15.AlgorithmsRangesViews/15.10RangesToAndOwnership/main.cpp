#include <algorithm>
#include <cctype>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

// Prints a label and the elements of a vector (as in 15.4).
template <typename T>
void show(std::string_view label, const std::vector<T>& values) {
    std::print("{:<24}", label);
    for (const T& value : values) {
        std::print(" {}", value);
    }
    std::println();
}

struct Reading {
    std::string station;
    double celsius;
};

std::vector<Reading> load_readings() {
    return {{"north", 18.5}, {"south", 24.0}, {"east", 21.5}, {"west", 16.0}};
}

int main() {

    // 15.9 used std::ranges::to<std::vector>() to look inside a view. It can
    // build other containers too, and that is how a pipeline of views ends.
    std::println("--- ranges::to: from a recipe to a container");
    std::vector<double> celsius{18.5, 24.0, 21.5, 16.0};

    auto fahrenheit{celsius
                    | std::views::transform([](double c) { return c * 9.0 / 5.0 + 32.0; })
                    | std::ranges::to<std::vector>()};               // the element type is deduced
    show("as a vector:", fahrenheit);

    auto distinct_hours{std::vector<int>{12, 6, 12, 18, 6} | std::ranges::to<std::set>()};
    std::print("as a set:           ");
    for (int hour : distinct_hours) {
        std::print(" {}", hour);
    }
    std::println();

    std::vector<std::string> stations{"north", "south", "east", "west"};
    auto table{std::views::zip(stations, celsius) | std::ranges::to<std::map>()};   // pairs become key and value
    std::print("zip into a map:      ");
    for (const auto& [station, value] : table) {
        std::print(" {}={}", station, value);
    }
    std::println();

    std::string word{"north"};
    auto shouted{word | std::views::transform([](unsigned char ch) { return static_cast<char>(std::toupper(ch)); })
                      | std::ranges::to<std::string>()};
    std::println("as a string:        {}", shouted);

    // A view runs its function EVERY time you iterate it. That is what lazy means,
    // and it is a cost if you walk the view twice.
    std::println("\n--- lazy means: computed again on every pass");
    int calls{0};
    auto doubled{std::views::iota(1, 5) | std::views::transform([&calls](int x) { ++calls; return x * 2; })};
    for ([[maybe_unused]] int x : doubled) {}
    for ([[maybe_unused]] int x : doubled) {}
    std::println("two passes over 4 elements: the function ran {} times", calls);

    calls = 0;
    auto stored{doubled | std::ranges::to<std::vector>()};           // evaluate ONCE, keep the results
    for ([[maybe_unused]] int x : stored) {}
    for ([[maybe_unused]] int x : stored) {}
    std::println("after ranges::to, then two passes: {} times", calls);

    // --- ownership ---------------------------------------------------------------
    // A view does not own its elements, it refers to a container that must
    // outlive it. An algorithm that returned an ITERATOR into a temporary
    // container would hand you a pointer to something already destroyed (14.4).
    // C++20 closes that hole: the algorithm returns a special empty type,
    // std::ranges::dangling, instead of an iterator.
    std::println("\n--- dangling");

    // auto found{std::ranges::find_if(load_readings(), [](const Reading& r) { return r.celsius > 20.0; })};
    // std::println("{}", found->station);      // does not compile: ranges::dangling is not an iterator

    // The fix: give the container a name, so it outlives the iterator.
    auto readings{load_readings()};
    auto hot{std::ranges::find_if(readings, [](const Reading& r) { return r.celsius > 20.0; })};
    std::println("with a named container: {}", hot->station);

    // Or ask for a VALUE, which is copied out before the temporary dies.
    double warmest{std::ranges::max(load_readings() | std::views::transform(&Reading::celsius))};
    std::println("or ask for a value: warmest is {}", warmest);

    // A few ranges are safe to search even as temporaries, because their
    // iterators do not point into storage that can die (they are called
    // "borrowed"): a std::string_view and an iota view are among them.
    std::println("find in iota(1, 10) as a temporary: {}", *std::ranges::find(std::views::iota(1, 10), 5));

    // A view over a temporary container is fine in a pipeline: since C++20 the
    // pipeline takes OWNERSHIP of an rvalue container, so nothing is left dangling.
    show("filter over a temporary:",
         load_readings() | std::views::filter([](const Reading& r) { return r.celsius > 20.0; })
                         | std::views::transform(&Reading::station)
                         | std::ranges::to<std::vector>());

    // The rules of thumb:
    //   * a view over a NAMED container stays valid while that container lives
    //     and is not modified: push_back, erase and the like invalidate it, as
    //     they invalidate iterators (14.4)
    //   * a view over a temporary container owns it: fine
    //   * a view that refers to something local must not be returned from the
    //     function that owns it
    //   * a view made with filter cannot be iterated through a const reference
    //     (its begin() remembers where the first match is, so it changes the
    //     view). The compiler says "discards qualifiers".
    return 0;
}
