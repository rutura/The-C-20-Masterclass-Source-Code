#include <algorithm>
#include <iterator>
#include <print>
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

int main() {

    std::vector<int> temperatures{21, 15, 24, 9, 18, 12, 24, 6, 15, 27};
    show("start:", temperatures);

    // sort (7.5) is not always what you need. Sorting everything costs
    // O(n log n); often the question is smaller than "all in order".
    std::println("\n--- sort, stable_sort, partial_sort, nth_element");

    std::vector<int> all{temperatures};
    std::ranges::sort(all);
    show("sort:", all);

    // stable_sort keeps equal elements in their original order. It matters
    // when you sort records by one field after sorting by another (15.8).

    // The 3 smallest, in order. Only the front is sorted; the rest is left in no
    // particular order.
    std::vector<int> three_coldest{temperatures};
    std::ranges::partial_sort(three_coldest, three_coldest.begin() + 3);
    show("partial_sort, first 3:", std::vector<int>(three_coldest.begin(), three_coldest.begin() + 3));

    // The median, without sorting the rest. nth_element puts the element that
    // WOULD be at position n in a sorted range there, with smaller ones before it
    // and larger ones after it, in no order.
    std::vector<int> for_median{temperatures};
    auto middle{for_median.begin() + for_median.size() / 2};
    std::ranges::nth_element(for_median, middle);
    std::println("median (position {}): {}", for_median.size() / 2, *middle);

    std::println("is_sorted? start: {}   sorted copy: {}",
                 std::ranges::is_sorted(temperatures), std::ranges::is_sorted(all));

    // partition: reorder so that everything satisfying a test comes first.
    std::println("\n--- partition, stable_partition, partition_point");
    auto cold{[](int t) { return t < 15; }};
    std::vector<int> split{temperatures};
    auto boundary{std::ranges::stable_partition(split, cold)};       // keeps the order inside each group
    show("cold first:", split);
    std::println("{} cold readings; the rest start at index {}", boundary.begin() - split.begin(), boundary.begin() - split.begin());

    // On a partitioned range, partition_point finds the boundary with a binary
    // search instead of a scan.
    auto point{std::ranges::partition_point(split, cold)};
    std::println("partition_point: index {}", point - split.begin());

    // Binary search on SORTED data (7.5 did binary_search). The family answers
    // more than "is it there": WHERE is it, and how many.
    std::println("\n--- lower_bound, upper_bound, equal_range");
    auto first_24{std::ranges::lower_bound(all, 24)};                // first element >= 24
    auto after_24{std::ranges::upper_bound(all, 24)};                // first element > 24
    std::println("lower_bound(24): index {}   upper_bound(24): index {}", first_24 - all.begin(), after_24 - all.begin());
    auto run{std::ranges::equal_range(all, 24)};
    std::println("24 appears {} times", run.size());
    auto first_over_20{std::ranges::upper_bound(all, 20)};
    std::println("readings above 20: {}", all.end() - first_over_20);

    // Sorted ranges can be combined in a single pass.
    std::println("\n--- merge and set operations on sorted ranges");
    std::vector<int> monday{6, 9, 12, 15, 18};
    std::vector<int> tuesday{9, 10, 15, 21};
    std::vector<int> both;
    std::ranges::merge(monday, tuesday, std::back_inserter(both));
    show("merge:", both);

    std::vector<int> either;
    std::ranges::set_union(monday, tuesday, std::back_inserter(either));
    show("set_union:", either);

    std::vector<int> common;
    std::ranges::set_intersection(monday, tuesday, std::back_inserter(common));
    show("set_intersection:", common);

    std::vector<int> only_monday;
    std::ranges::set_difference(monday, tuesday, std::back_inserter(only_monday));
    show("set_difference:", only_monday);

    std::println("monday includes {{9, 15}}: {}", std::ranges::includes(monday, std::vector<int>{9, 15}));

    // All of these REQUIRE sorted input (with the same ordering). On unsorted
    // data they compile and run and quietly give wrong answers.
    return 0;
}
