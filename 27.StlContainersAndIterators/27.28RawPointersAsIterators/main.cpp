#include <algorithm>
#include <print>
#include <ranges>
#include "boxcontainer.h"

template <typename T>
void print(const BoxContainer<T>& c) {
    for (auto i : c) { // Computation happens here.
        std::print("{} ", i);
    }
    std::println("");
}

int main() {

    BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(7);
    vi.add(2);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);

    const BoxContainer<int> copy(vi);

    // Printing a const container
    std::print("data : ");
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    // Printing through a function
    std::print("copy : ");
    print(copy);

    // std::ranges::sort(copy); // compiler error - can't sort a const collection
    std::ranges::sort(vi);

    std::print("vi : ");
    print(vi);

    std::print("view taking only 3 : ");
    for (auto i : std::views::take(vi, 3)) {
        std::print("{} ", i);
    }
    std::println("");

    std::println("End!");

    return 0;
}
