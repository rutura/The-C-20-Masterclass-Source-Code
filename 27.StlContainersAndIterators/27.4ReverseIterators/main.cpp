#include <print>
#include <vector>

int main() {

    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // A reverse iterator increments backwards from the end - rbegin() starts
    // at the last element, rend() marks one-before-the-first.
    std::vector<int>::reverse_iterator it = numbers.rbegin();
    *it = 34; // rbegin() points at a real element, so it's writable too
    std::print("Numbers : [");
    while (it != numbers.rend()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("] ");

    std::println("--------");

    // A reverse_iterator can't be compared against a regular end() - they're
    // different iterator types walking the container in opposite
    // directions, so this wouldn't compile:
    // auto it_rev = numbers.rbegin();
    // if (it_rev != numbers.end()) { ... } // compiler error

    return 0;
}