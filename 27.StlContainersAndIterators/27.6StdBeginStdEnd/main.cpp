#include <print>

int main() {

    // A C-style array has no .begin()/.end() member functions of its own -
    // vi.begin() wouldn't compile. std::begin()/std::end() are free
    // functions that work uniformly across C-style arrays and any
    // container that does have begin()/end() members.
    int vi[]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::println("--------");

    std::print(" Collection : ");
    for (auto it = std::begin(vi); it != std::end(vi); ++it) {
        std::print("{} ", *it);
    }
    std::println("");

    return 0;
}