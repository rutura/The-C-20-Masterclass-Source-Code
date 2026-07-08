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

    // A const BoxContainer needs begin()/end() to return a ConstIterator
    // (one that can read but not write) - the non-const Iterator overload
    // wouldn't even be visible on a const object.
    std::print("data : ");
    for (auto it = copy.begin(); it != copy.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    print(copy);

    return 0;
}
