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

    std::println("box1 : {}", box1);

    // std::ranges::sort needs a random access iterator - it needs to jump
    // to any position in constant time (it + n) to divide and conquer
    // efficiently, which bidirectional's operator--/++ alone can't give.
    std::ranges::sort(box1.begin(), box1.end());

    std::println("box1 : {}", box1);

    return 0;
}
