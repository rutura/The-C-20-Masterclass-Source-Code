#include <array>
#include <cstddef>
#include <print>
#include <span>
#include <vector>

// One function, any contiguous run of ints: a built-in array, a std::array, a
// std::vector, a slice of any of them. span<const int> is read-only, the
// same idea as const int* from 9.3.
double average(std::span<const int> values) {
    if (values.empty()) {
        return 0.0;
    }

    int total{0};
    for (int value : values) {
        total += value;
    }
    return static_cast<double>(total) / static_cast<double>(values.size());
}

// span<int> (no const) lets the function change the caller's elements.
void add_offset(std::span<int> values, int offset) {
    for (int& value : values) {
        value += offset;
    }
}

int main() {

    // A span is a (pointer, count) pair promoted to a type. It is what 9.5's
    // print_all(const int*, std::size_t) was trying to be, with the two
    // pieces welded together so they cannot disagree. Like std::string_view
    // (7.9), it OWNS nothing and copies nothing.
    int built_in[5]{68, 71, 69, 72, 70};
    std::array<int, 5> fixed{68, 71, 69, 72, 70};
    std::vector<int> growable{68, 71, 69, 72, 70};

    std::println("built-in array: {:.1f}", average(built_in));
    std::println("std::array:     {:.1f}", average(fixed));
    std::println("std::vector:    {:.1f}", average(growable));

    // Slicing without copying: each of these is a new view over the SAME
    // elements.
    std::span<const int> all{growable};
    std::println("\nfirst(3)      = {} elements, average {:.1f}", all.first(3).size(), average(all.first(3)));
    std::println("last(2)       = {} elements, average {:.1f}", all.last(2).size(), average(all.last(2)));
    std::println("subspan(1, 3) = {} elements, average {:.1f}", all.subspan(1, 3).size(), average(all.subspan(1, 3)));

    // Because it shares the elements, writing through a non-const span
    // changes the original.
    add_offset(growable, 10);
    std::println("\nafter add_offset(growable, 10): front = {}, back = {}", growable.front(), growable.back());

    // Only part of the container: the first three are adjusted again.
    add_offset(std::span<int>{growable}.first(3), -10);
    std::println("after adjusting only the first three: {} {} {} {} {}",
                 growable[0], growable[1], growable[2], growable[3], growable[4]);

    // The old pointer-and-count pair converts directly.
    const int* pointer{fixed.data()};
    std::span<const int> from_pair{pointer, 4};
    std::println("\nfrom a pointer and a count of 4: average {:.1f}", average(from_pair));

    // Indexing works, but a span does not check the index for you. Use
    // size() when in doubt.
    std::println("from_pair[0] = {}, from_pair.size() = {}, size_bytes = {}",
                 from_pair[0], from_pair.size(), from_pair.size_bytes());

    // Gotcha: a span dangles exactly like a pointer. If the vector grows and
    // moves its elements, every span over it is left looking at freed memory.
    //
    //     std::span<const int> view{growable};
    //     growable.push_back(75);         // may reallocate
    //     view[0];                        // possibly a dangling read
    //
    // Treat a span as a short-lived way to PASS data to a function, and do
    // not keep it while the container changes.
    return 0;
}
