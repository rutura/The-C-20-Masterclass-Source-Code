#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdint>
#include <print>
#include <random>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 6 assignment - solutions

    Each exercise keeps its problem statement and sample output in a
    comment above the solution, so this file reads on its own. The
    running theme is a tiny terminal stats / bar-chart tool over a fixed
    list of numbers.
*/

// ---------------------------------------------------------------------
// Exercise 1 - stats() with reference out-parameters
//
// Prototype here, definition after main. Scans the data once and writes
// low / high / mean back through the reference parameters.
//
// Sample output:
//     low = 5, high = 88, mean = 45.625
// ---------------------------------------------------------------------
void stats(const std::vector<int>& data, int& low, int& high, double& mean);

// ---------------------------------------------------------------------
// Exercise 2 - bar() with default arguments + std::clamp
//
// Defaults live in this prototype only. std::clamp keeps `value` inside
// [0, width] so the bar can never be negative or overrun the width.
//
// Sample output: see the exercise block in main.
// ---------------------------------------------------------------------
void bar(int value, int width = 40, char fill = '*');

// ---------------------------------------------------------------------
// Exercise 3 - clamp_to<T>: a template instantiated for int and double
//
// Same behaviour as std::clamp; written out so we see one template
// stamped into two concrete functions.
// ---------------------------------------------------------------------
template <typename T>
T clamp_to(T value, T lo, T hi) {
    if (value < lo) { return lo; }
    if (value > hi) { return hi; }
    return value;
}

// ---------------------------------------------------------------------
// Exercise 4 - describe() overloaded three ways
//
// Same name, three different signatures. The compiler picks the match
// from the argument's type. describe(4.0) needs the .0 or it calls the
// int overload.
//
// Sample output:
//     int 88, even
//     double 3.5, fractional
//     double 4, whole
//     text "apple", 5 chars, starts with a vowel: yes
//     text "banana", 6 chars, starts with a vowel: no
// ---------------------------------------------------------------------
void describe(int n) {
    std::println("int {}, {}", n, (n % 2 == 0) ? "even" : "odd");
}

void describe(double x) {
    const bool whole{std::floor(x) == x};
    std::println("double {}, {}", x, whole ? "whole" : "fractional");
}

void describe(std::string_view s) {
    // starts_with (C++20) tests a prefix; check the five vowels against
    // the front of the string.
    const bool vowel{s.starts_with('a') || s.starts_with('e') ||
                     s.starts_with('i') || s.starts_with('o') ||
                     s.starts_with('u')};
    std::println("text \"{}\", {} chars, starts with a vowel: {}",
                 s, s.size(), vowel ? "yes" : "no");
}

// ---------------------------------------------------------------------
// Exercise 5 - next_roll() with a static local RNG
//
// engine and die are static: constructed once, on the first call, then
// reused. Seeding from random_device happens exactly once too, because
// the initializer of a static local runs only the first time control
// passes through it.
//
// Sample output (differs every run):
//     rolls: 4 1 6 3 3 5 2 6
// ---------------------------------------------------------------------
int next_roll() {
    static std::default_random_engine engine{std::random_device{}()};
    static std::uniform_int_distribution<int> die{1, 6};
    return die(engine);
}

// ---------------------------------------------------------------------
// Exercise 6a - digit_sum(): recursive
//
// Base case: n < 10 returns n. Step: last digit plus digit_sum of the
// rest. [[nodiscard]] because throwing the result away is always a bug.
//
// Sample output:
//     digit_sum(42)    = 6
//     digit_sum(12345) = 15
//     digit_sum(365)   = 14
// ---------------------------------------------------------------------
[[nodiscard]] long digit_sum(long n) {
    if (n < 10) {
        return n;                        // base case - single digit
    }
    return (n % 10) + digit_sum(n / 10); // recursive step
}

// ---------------------------------------------------------------------
// Exercise 6b - digit_sum_iterative(): the same result as a loop
//
// One stack frame, an explicit accumulator - the iterative counterpart
// of the recursion above.
// ---------------------------------------------------------------------
long digit_sum_iterative(long n) {
    long total{0};
    while (n > 0) {
        total += n % 10;
        n /= 10;
    }
    return total;
}

// ---------------------------------------------------------------------
// Exercise 7 - checksum() with [[nodiscard]] and a lambda
//
// Rolling hash:  acc = acc * 31 + element, for each element. The
// accumulation is done by a lambda capturing acc by reference. Marked
// [[nodiscard]] so `checksum(samples);` on its own line would warn.
//
// Sample output:
//     checksum(samples) = <deterministic int>
// ---------------------------------------------------------------------
[[nodiscard]] int checksum(const std::vector<int>& data) {
    int acc{0};
    auto fold = [&acc](int element) { acc = acc * 31 + element; };
    for (int element : data) {
        fold(element);
    }
    return acc;
}

// ---------------------------------------------------------------------
// Exercise 8 - pack three bytes into one std::uint32_t
//
// Mirrors the image project: three channel bytes packed into a wider
// integer. Layout: red is the top byte of the low 24 bits, then green,
// then blue.
//
//     bits: 23..16   15..8    7..0
//              R        G       B
//
// Sample output:
//     packed      = 0xf08c28
//     red         = 240
//     green       = 140
//     blue        = 40
//     popcount    = 11
//     power of 2? = false
// ---------------------------------------------------------------------
std::uint32_t pack_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    // Cast each byte to the wide type BEFORE shifting: `r << 16` done in
    // 8-bit arithmetic would lose every bit. (In practice r is promoted
    // to int here, but being explicit matches the intent and the image
    // chapter's advice about doing width-sensitive math in the wide type.)
    return (static_cast<std::uint32_t>(r) << 16) |
           (static_cast<std::uint32_t>(g) << 8) |
           static_cast<std::uint32_t>(b);
}

std::uint8_t channel(std::uint32_t packed, int which) {
    // which: 0 = red (top byte), 1 = green, 2 = blue (bottom byte).
    // Red sits highest, so it needs the biggest right-shift.
    const int shift{(2 - which) * 8};
    return static_cast<std::uint8_t>((packed >> shift) & 0xFFu);
}

int main() {

    const std::vector<int> samples{42, 17, 88, 5, 63, 29, 71, 50};

    // --- Exercise 1 ---
    std::println("--- Exercise 1: stats ---");
    {
        int low{};
        int high{};
        double mean{};
        stats(samples, low, high, mean);
        std::println("low = {}, high = {}, mean = {}", low, high, mean);
    }

    // --- Exercise 2 ---
    std::println("\n--- Exercise 2: bar ---");
    {
        for (int value : samples) {
            bar(value / 2);           // all defaults: width 40, fill '*'
        }
        bar(1000);                    // clamped down to width (40)
        bar(20, 20, '=');             // all three arguments given
    }

    // --- Exercise 3 ---
    std::println("\n--- Exercise 3: clamp_to<T> ---");
    {
        std::println("clamp_to(120, 0, 100)     = {}", clamp_to(120, 0, 100));
        std::println("clamp_to(-2.5, 0.0, 1.0)  = {}", clamp_to(-2.5, 0.0, 1.0));
        std::println("std::clamp(120, 0, 100)   = {}", std::clamp(120, 0, 100));
    }

    // --- Exercise 4 ---
    std::println("\n--- Exercise 4: describe (overloading) ---");
    {
        describe(88);
        describe(3.5);
        describe(4.0);       // the .0 matters: describe(4) would call describe(int)
        describe("apple");
        describe("banana");
    }

    // --- Exercise 5 ---
    std::println("\n--- Exercise 5: next_roll (static local RNG) ---");
    {
        std::print("rolls:");
        for (int i{0}; i < 8; ++i) {
            std::print(" {}", next_roll());
        }
        std::println("");
    }

    // --- Exercise 6 ---
    std::println("\n--- Exercise 6: digit_sum ---");
    {
        long samples_total{0};
        for (int value : samples) {
            samples_total += value;
        }

        for (long n : {42L, 12345L, samples_total}) {
            std::println("digit_sum({}) = {}   (iterative: {})",
                         n, digit_sum(n), digit_sum_iterative(n));
        }
    }

    // --- Exercise 7 ---
    std::println("\n--- Exercise 7: checksum ---");
    {
        std::println("checksum(samples) = {}", checksum(samples));
        // checksum(samples);   // would warn: [[nodiscard]] result ignored
    }

    // --- Exercise 8 ---
    std::println("\n--- Exercise 8: pack_rgb ---");
    {
        const std::uint32_t packed{pack_rgb(240, 140, 40)};   // image project's orange
        std::println("packed      = {:#08x}", packed);
        std::println("red         = {}", channel(packed, 0));
        std::println("green       = {}", channel(packed, 1));
        std::println("blue        = {}", channel(packed, 2));
        std::println("popcount    = {}", std::popcount(packed));
        std::println("power of 2? = {}", std::has_single_bit(packed));
    }

    return 0;
}

// ---------------------------------------------------------------------
// Exercise 1 definition, after main.
// ---------------------------------------------------------------------
void stats(const std::vector<int>& data, int& low, int& high, double& mean) {
    long sum{0};
    low = data.front();
    high = data.front();
    for (int value : data) {
        low = std::min(low, value);
        high = std::max(high, value);
        sum += value;
    }
    mean = static_cast<double>(sum) / static_cast<double>(data.size());
}

// ---------------------------------------------------------------------
// Exercise 2 definition. No defaults here - they are on the prototype.
// ---------------------------------------------------------------------
void bar(int value, int width, char fill) {
    const int length{std::clamp(value, 0, width)};
    std::println("{}", std::string(static_cast<std::size_t>(length), fill));
}
