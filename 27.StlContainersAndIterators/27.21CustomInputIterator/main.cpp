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

    // std::ranges::find only needs an input iterator: readable, and
    // incrementable in a single forward pass.
    if (std::ranges::find(box1, 8) != box1.end()) {
        std::println("numbers contains: 8");
    } else {
        std::println("numbers does not contain: 8");
    }

    // std::ranges::reverse(box1.begin(),box1.end()); // would need a
    // bidirectional iterator - BoxContainer's Iterator doesn't have
    // operator-- yet at this point in the chapter.

    // Range-based for loop
    /*
    for (auto n : box1) {
        std::print("{} ", n);
    }
    std::println("");
    */

    return 0;
}
