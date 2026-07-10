// This program is a "feature probe": instead of just printing a version
// number, it actually tries to use a few C++20/23 features this course
// depends on. If your compiler is too old, this file won't compile at all -
// and the error the compiler gives you tells you exactly which feature is
// missing, which is more useful than a version number alone.

#include <print>
#include <concepts>

// C++20 concepts: constrains T to anything that supports operator+.
template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

template <Addable T>
T add(T a, T b) {
    return a + b;
}

int main() {

    std::println("If you can read this, your compiler supports:");

    // 1. std::print / std::println (C++23, <print>)
    std::println(" - std::println (C++23)");

    // 2. Concepts (C++20)
    std::println(" - concepts: 2 + 3 = {}", add(2, 3));

    // 3. Digit separators (C++14, but a good sanity check alongside the rest)
    constexpr int million{1'000'000};
    std::println(" - digit separators: {}", million);

    std::println("\nYou're ready for this course's C++23 examples.");

    return 0;
}
