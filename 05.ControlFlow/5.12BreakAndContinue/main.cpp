#include <print>

int main() {

    // --- break: leave the loop entirely, right now ---
    int page{};
    for (page = 1; page <= 10; ++page) {
        if (page == 5) {
            break;                  // page torn out - stop reading here
        }
        std::print("{} ", page);
    }
    std::println("\nStopped reading at page {}\n", page);

    // --- continue: skip the rest of THIS iteration, go to the next ---
    for (int p{1}; p <= 10; ++p) {
        if (p == 5) {
            continue;               // page 5 is blank - jump to ++p and the next test
        }
        std::print("{} ", p);
    }
    std::println("\nUsed continue to skip the blank page 5");

    // In a for loop, `continue` still runs the update step (++p) before
    // re-testing. In a while loop it does not - a `continue` that jumps
    // over your `++page` there gives you an infinite loop.

    return 0;
}
