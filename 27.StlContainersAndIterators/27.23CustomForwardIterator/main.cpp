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

    // std::ranges::replace needs a forward iterator: it has to walk the
    // range, comparing as it goes, and be able to make that same pass more
    // than once if the algorithm needs to - a guarantee an input iterator
    // alone doesn't give.
    std::ranges::replace(box1.begin(), box1.end(), 7, 777);
    std::println("box1 : {}", box1);

    return 0;
}
