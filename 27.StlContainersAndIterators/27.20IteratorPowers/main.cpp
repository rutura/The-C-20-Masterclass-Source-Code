#include <algorithm>
#include <format>
#include <print>
#include <ranges>
#include <vector>

template <typename T>
struct std::formatter<std::vector<T>> : std::formatter<std::string> {
    auto format(const std::vector<T>& vec, std::format_context& ctx) const {
        std::string out = "[ ";
        for (auto i : vec) {
            out += std::format("{} ", i);
        }
        out += "]";
        return std::formatter<std::string>::format(out, ctx);
    }
};

int main() {

    std::vector<int> numbers{1, 9, 3, 7, 2, 5, 4, 6, 89};
    std::println("numbers : {}", numbers);

    // Each block below needs progressively more from its iterator - this
    // lecture is a tour of the five iterator categories, uncommented one at
    // a time as each is introduced, rather than all at once.

    // Input iterator: only needs to be readable and incrementable once,
    // single-pass. That's all std::ranges::find needs.
    /*
    if (std::ranges::find(numbers.cbegin(), numbers.cend(), 8) != numbers.cend()) {
        std::println("numbers contains: 8");
    } else {
        std::println("numbers does not contain: 8");
    }
    */

    // Output iterator: an iterator through which you can write.
    /*
    std::println("---------------(copy)-----------");
    std::vector<int> dest(numbers.size());
    // std::vector<int> dest; // BAD! Probably a crash - copy needs room to write into.
    std::println("numbers : {}", numbers);
    std::println("dest : {}", dest);

    // dest.begin() has to be an output iterator - has to be writable through.
    std::ranges::copy(numbers.cbegin(), numbers.cend(), dest.begin());
    std::println("numbers : {}", numbers);
    std::println("dest : {}", dest);
    */

    // Forward iterator: needs operator++ to move forward, and needs to
    // support making that same pass more than once (multi-pass guarantee).
    /*
    std::println("---------------(replace)-------------");
    std::println("numbers : {}", numbers);

    std::ranges::replace(numbers.begin(), numbers.end(), 7, 345);
    std::println("numbers : {}", numbers);
    */

    // Bidirectional iterator: adds operator-- to move backward too.
    /*
    std::println("---------------(bi-directional)-------------");
    std::println("numbers : {}", numbers);
    auto it_first = numbers.begin();
    auto it_last = numbers.end();
    while (it_last-- != it_first) {
        std::print("{} ", *it_last);
    }
    std::println("");

    std::ranges::reverse(numbers.begin(), numbers.end());
    std::println("numbers : {}", numbers);
    */

    // Random access iterator: jumps to any position in constant time
    // (it + n), which sort needs to divide-and-conquer efficiently.
    /*
    std::println("---------------(sort)-------------");
    std::println("numbers : {}", numbers);

    std::ranges::sort(numbers);
    std::println("numbers : {}", numbers);
    */

    return 0;
}
