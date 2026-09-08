#include <print>

int main() {

    // --- break: leave the loop entirely, right now ---
    int count{};
    for (count = 1; count <= 10; ++count) {
        if (count == 5) {
            break;                  // no more iterations happen
        }
        std::print("{} ", count);
    }
    std::println("\nBroke out of the loop at count = {}\n", count);

    // --- continue: skip the rest of THIS iteration, go to the next ---
    for (int i{1}; i <= 10; ++i) {
        if (i == 5) {
            continue;               // jump straight to ++i and the next test
        }
        std::print("{} ", i);
    }
    std::println("\nUsed continue to skip printing 5");

    // In a for loop, `continue` still runs the update step (++i) before
    // re-testing. In a while loop it does not - a `continue` that jumps
    // over your `++counter` there gives you an infinite loop.

    return 0;
}
