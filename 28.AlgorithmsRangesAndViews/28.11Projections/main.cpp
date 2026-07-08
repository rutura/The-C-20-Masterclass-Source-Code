#include <print>
#include <algorithm>
#include <utility>
#include <vector>
#include "point.h"

template <typename T>
void print_collection(const T& collection) {
    std::print(" Collection [");
    for (const auto& elt : collection) {
        std::print(" {}", elt);
    }
    std::println("]");
}

int main() {

    // Sorting normally compares elements directly with operator< (or a
    // comparator) - but sometimes you want to order by a different member
    // or computed value than the one operator< uses. A projection lets you
    // say "compare by this instead" without writing a new comparator.
    std::println("");
    std::println("Sorting points (default : based on length) : ");
    std::vector<Point> points{{10, 90}, {30, 70}, {20, 80}};

    print_collection(points);

    std::ranges::sort(points, std::less<>{}); // default: sorts by Point's own operator<=>
    print_collection(points);

    // The projection runs on each element before the comparator sees it -
    // std::less<> ends up comparing two doubles (m_x), not two Points.
    std::println("");
    std::println("projection on Point::m_x : ");
    print_collection(points);
    std::ranges::sort(points, std::less<>{}, [](auto const& p) { return p.m_x; });
    print_collection(points);

    // A pointer-to-member works directly as a projection too, no lambda needed.
    std::println("");
    std::println("projection on Point::m_y with direct member variables : ");
    print_collection(points);
    std::ranges::sort(points, std::less<>{}, &Point::m_y);
    print_collection(points);

    // Projections work on for_each too - the projection picks what each
    // call to the function actually sees.
    std::println("");
    std::println("Projections with for_each : ");

    auto print = [](const auto& n) { std::print(" {}", n); };
    using pair = std::pair<int, std::string>;
    std::vector<pair> pairs{{1, "one"}, {2, "two"}, {3, "tree"}};

    std::print("project the pair::first: ");
    std::ranges::for_each(pairs, print, [](const pair& p) { return p.first; });
    std::println("");

    std::print("project the pair::first: ");
    std::ranges::for_each(pairs, print, &pair::first);
    std::println("");

    std::print("project the pair::second: ");
    std::ranges::for_each(pairs, print, [](const pair& p) { return p.second; });
    std::println("");

    return 0;
}