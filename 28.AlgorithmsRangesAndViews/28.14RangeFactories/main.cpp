#include <print>
#include <ranges>

int main() {

    // std::views::iota(1) is a range factory: an infinite sequence of
    // integers starting at 1, generated lazily - each value is produced
    // only as the loop asks for it, not computed up front. Piping it
    // through views::take(20) caps how many values the loop actually sees.
    for (auto i : std::views::iota(1) | std::views::take(20)) {
        std::println("{}", i);
    }

    return 0;
}