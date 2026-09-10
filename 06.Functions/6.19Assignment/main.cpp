#include <bit>
#include <cmath>
#include <cstdint>
#include <print>
#include <random>
#include <string_view>
#include <vector>

/*
    Chapter 6 assignment - Functions

    One small program built in eight steps. Each exercise pulls in a
    different part of the chapter: prototypes and definitions, the
    library tour (<cmath>, <numeric>, <algorithm>, <string>, <bit>),
    default arguments, reference parameters, overloading, templates,
    random numbers, static locals, recursion, [[nodiscard]], lambdas,
    and the fixed-width integer types from the image project.

    The theme is a tiny terminal stats / bar-chart tool: given a list of
    numbers, describe them and draw them.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - In sample runs, text after a ">" is what the user typed.
*/

int main() {

    // A fixed dataset the whole program works on. Treat it as given.
    const std::vector<int> samples{42, 17, 88, 5, 63, 29, 71, 50};


    /*
        Exercise 1 - stats() with reference out-parameters

        Declare a PROTOTYPE above main and define it AFTER main:

            void stats(const std::vector<int>& data,
                       int& low, int& high, double& mean);

        It scans `data` once and writes three results back through the
        reference parameters: the smallest value, the largest value, and
        the arithmetic mean (sum / count, as a double). Use std::min and
        std::max from <algorithm> for the running low/high.

        Call it on `samples`, then print the three values.

        Sample output:
            low = 5, high = 88, mean = 45.625
    */
    std::println("--- Exercise 1: stats ---");
    // TODO


    /*
        Exercise 2 - bar() with default arguments + std::clamp

        Write:

            void bar(int value, int width = 40, char fill = '*');

        It prints a bar: `value` clamped into [0, width] with
        std::clamp (<algorithm>), then that many `fill` characters, then
        a newline. The default width is 40, the default fill is '*'.
        Defaults go in the PROTOTYPE only, never repeated in the
        definition.

        Call it: once for each value in `samples` scaled down by 2
        (so 42 -> 21 stars), using all defaults; then once as
        bar(1000) to show the clamp capping an out-of-range value at
        `width`; then once as bar(20, 20, '=').

        Sample output:
            *********************
            ********
            ****************************************
            **
            *******************************
            **************
            ***********************************
            *************************
            ****************************************   (bar(1000), clamped)
            ====================                       (bar(20, 20, '='))
    */
    std::println("\n--- Exercise 2: bar ---");
    // TODO


    /*
        Exercise 3 - a clamp_to<T> template, next to std::clamp

        Write your own:

            template <typename T>
            T clamp_to(T value, T lo, T hi);

        returning `lo` if value < lo, `hi` if value > hi, else value.
        This is what std::clamp already does - the point is to see a
        template instantiated for more than one type.

        Call it with ints: clamp_to(120, 0, 100)  -> 100
        Call it with doubles: clamp_to(-2.5, 0.0, 1.0) -> 0.0
        Then call std::clamp with the same int arguments and confirm the
        two agree.

        Sample output:
            clamp_to(120, 0, 100)     = 100
            clamp_to(-2.5, 0.0, 1.0)  = 0
            std::clamp(120, 0, 100)   = 100
    */
    std::println("\n--- Exercise 3: clamp_to<T> ---");
    // TODO


    /*
        Exercise 4 - describe() overloaded three ways

        Three functions, same name, different signature (this is
        overloading - the compiler picks by the argument types):

            void describe(int n);
            void describe(double x);
            void describe(std::string_view s);

        - describe(int):    prints "int <n>, <even|odd>"
        - describe(double): prints "double <x>, <whole|fractional>"
                            (whole when std::floor(x) == x)
        - describe(std::string_view): prints
                            "text \"<s>\", <N> chars, starts with a vowel: <yes|no>"
                            using s.size() and s.starts_with(...) or
                            s.contains(...) from <string_view>.

        Call all three: describe(88), describe(3.5), describe(4.0),
        describe("apple"), describe("banana").

        Note describe(4.0) - the literal must be 4.0, not 4, or it calls
        the int overload. Mention that in a comment.

        Sample output:
            int 88, even
            double 3.5, fractional
            double 4, whole
            text "apple", 5 chars, starts with a vowel: yes
            text "banana", 6 chars, starts with a vowel: no
    */
    std::println("\n--- Exercise 4: describe (overloading) ---");
    // TODO


    /*
        Exercise 5 - next_roll() with a static local RNG

        Write:

            int next_roll();

        that returns a random integer in 1..6. The engine and the
        distribution are STATIC LOCALS inside the function, so they are
        built once (on the first call) and reused on every later call -
        not recreated each time. Seed the engine from std::random_device
        the first time.

        Call next_roll() eight times and print the results on one line.
        (The numbers differ every run; each is in 1..6.)

        Sample output (numbers will differ):
            rolls: 4 1 6 3 3 5 2 6
    */
    std::println("\n--- Exercise 5: next_roll (static local RNG) ---");
    // TODO


    /*
        Exercise 6 - digit_sum(), recursive and iterative

        (a) [[nodiscard]] long digit_sum(long n) - RECURSIVE.
            Base case: a single digit (n < 10) returns n.
            Recursive step: (n % 10) + digit_sum(n / 10).
            Assume n >= 0.

        (b) long digit_sum_iterative(long n) - the same result with a
            while loop and an accumulator, no recursion.

        Print both for 42, for 12345, and for the sum of `samples`
        (add the eight numbers up first). The recursive and iterative
        results must match.

        Sample output:
            digit_sum(42)        = 6    (iterative: 6)
            digit_sum(12345)     = 15   (iterative: 15)
            digit_sum(365)       = 14   (iterative: 14)   [365 = sum of samples]
    */
    std::println("\n--- Exercise 6: digit_sum ---");
    // TODO


    /*
        Exercise 7 - checksum() with [[nodiscard]] and a lambda

        Write:

            [[nodiscard]] int checksum(const std::vector<int>& data);

        It returns a running value computed like this: start at 0, and
        for each element run  acc = acc * 31 + element  (a classic
        rolling hash). Do the accumulation with a lambda captured by
        reference ([&acc]) that you call once per element in a range-for
        loop.

        Because checksum is [[nodiscard]], calling it and ignoring the
        result must produce a compiler warning. Show that you use it:
        print checksum(samples). Then add a commented-out line
        `// checksum(samples);` with a note that it would warn.

        Sample output:
            checksum(samples) = <some int>       (deterministic - same every run)
    */
    std::println("\n--- Exercise 7: checksum ---");
    // TODO


    /*
        Exercise 8 - pack three bytes into one std::uint32_t

        This mirrors the image project: three small channel values
        squeezed into one wider integer.

        (a) Write:

                std::uint32_t pack_rgb(std::uint8_t r,
                                       std::uint8_t g,
                                       std::uint8_t b);

            returning (r << 16) | (g << 8) | b. Cast r/g/b to
            std::uint32_t before shifting so the shift has room.

        (b) Write:

                std::uint8_t channel(std::uint32_t packed, int which);

            where which == 0 returns the red byte, 1 green, 2 blue.
            From part (a)'s layout, red sits in bits 23..16, green in
            15..8, blue in 7..0 - so red needs the biggest right-shift.
            Shift right by (2 - which) * 8, then mask with 0xFF.

        Pack (240, 140, 40) - the image project's orange. Print the
        packed value in hex with {:#08x}, then print the three channels
        read back out. Also print std::popcount(packed) and
        std::has_single_bit(packed) from <bit>.

        Sample output:
            packed      = 0xf08c28
            red         = 240
            green       = 140
            blue        = 40
            popcount    = 11
            power of 2? = false
    */
    std::println("\n--- Exercise 8: pack_rgb ---");
    // TODO


    return 0;
}
