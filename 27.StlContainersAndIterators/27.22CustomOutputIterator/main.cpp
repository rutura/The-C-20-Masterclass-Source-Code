#include <algorithm>
#include <print>
#include <ranges>
#include "boxcontainer.h"

int main() {

    BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);

    std::println("box : {}", box1);

    // Destination box, pre-filled with placeholder values so it already
    // has somewhere for std::ranges::copy to write into.
    BoxContainer<int> box2;
    for (size_t i{}; i < box1.size(); ++i) {
        box2.add(0);
    }

    std::println("box2-1 : {}", box2);
    // box2.begin() needs to be an output iterator here - writable, not just
    // readable - which is exactly what this lecture's Iterator now supports.
    std::ranges::copy(box1, box2.begin());
    std::println("box2-2 : {}", box2);

    return 0;
}
