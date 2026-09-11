#include <bit>
#include <cmath>
#include <cstdint>
#include <print>
#include <random>
#include <string_view>
#include <vector>

/*
    Chapter 6 assignment - Functions

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - In sample runs, text after a ">" is what the user typed.
*/

int main() {

    // A fixed dataset we will be working on
    const std::vector<int> samples{42, 17, 88, 5, 63, 29, 71, 50};


    /*
        Exercise 1 - stats() with reference out-parameters

        Declare a PROTOTYPE above main and define it AFTER main:

            void stats(const std::vector<int>& data,
                       int& low, int& high, double& mean);

        It scans (loops through) `data` once and writes three results back through the
        reference parameters: the smallest value, the largest value, and
        the arithmetic mean (sum / count, as a double). You have the freedom to name
        the variables that are passed to the function as input. Use std::min and
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

        Think of it as drawing one row of a text bar chart: it prints
        `fill` repeated `value` times, so bar(5) prints "*****".

        `width` is the cap - the longest the bar is allowed to be. If
        `value` is bigger than `width`, only print `width` characters
        (so the bar never runs longer than the row it's drawn in); if
        `value` is negative, print nothing. Use std::clamp (<algorithm>)
        to turn `value` into that final character count in one line
        instead of writing the if/else yourself.

        The default width is 40, the default fill is '*'. Defaults go
        in the PROTOTYPE only, never repeated in the definition.

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

        A checksum is a single number squeezed out of a whole collection
        of data, used to catch corruption or mistakes: if you compute the
        checksum before sending a file and again after receiving it, and
        the two numbers don't match, something changed along the way -
        even if you never look at the data itself. You don't need to
        know exactly how the number was produced to use it this way; you
        only need it to reliably change whenever the input does, and to
        reproduce the exact same number for the exact same input.

        Write:

            [[nodiscard]] int checksum(const std::vector<int>& data);

        It folds every element into one int, one at a time, using this
        rule, starting from acc = 0:

            acc = acc * 31 + element

        Worked example for {1, 2, 3}:

            acc = 0
            acc = 0 * 31 + 1  = 1      (after folding in 1)
            acc = 1 * 31 + 2  = 33     (after folding in 2)
            acc = 33 * 31 + 3 = 1026   (after folding in 3)   <- final checksum

        Change any one element - say {1, 2, 4} instead of {1, 2, 3} -
        and the final number comes out completely different, which is
        exactly the point: the result is sensitive to every value that
        went in.

        Do the folding with a lambda captured by reference ([&acc]) that
        you call once per element in a range-for loop, instead of writing
        the "acc = acc * 31 + element" line directly in the loop body.

        Because checksum is [[nodiscard]], calling it and ignoring the
        result may( depending on the warning level) produce a compiler 
        warning - the compiler is telling you "why did you even call 
        this function if you're not going to look at what it gives back?". 
        Try to use it and see if your compiler throws a warning: print
        checksum(samples). Then add a commented-out line
        `// checksum(samples);` with a note that it would warn.

        Sample output:
            checksum(samples) = <some int>       (deterministic - same every run)
    */
    std::println("\n--- Exercise 7: checksum ---");
    // TODO

    return 0;
}
