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

    // std::ranges::reverse needs a bidirectional iterator - it walks the
    // range from both ends inward, swapping as it goes, which needs
    // operator-- as well as operator++.
    std::println("box1 : {}", box1);
    std::ranges::reverse(box1);
    std::println("box1 : {}", box1);

    // The same walk written by hand, using operator-- directly instead of
    // going through an algorithm.
    std::print("box1-reverse : ");
    for (auto it = box1.end(); it != box1.begin();) {
        std::print("{} ", *(--it));
    }
    std::println("");

    return 0;
}
