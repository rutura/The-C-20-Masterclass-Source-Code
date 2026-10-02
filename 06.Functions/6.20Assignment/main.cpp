#include <bit>
#include <cmath>
#include <cstdint>
#include <print>
#include <random>
#include <string_view>
#include <algorithm>
#include <vector>
#include "image.h"

//#include "image.h"

/*
    Chapter 6 assignment - Functions

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - In sample runs, text after a ">" is what the user typed.
*/

//----------------------------------------------------------------
//Exercise 1
void stats(const std::vector<int>& data,
            int& low, int& high, double& mean); // Declaration
//----------------------------------------------------------------


//----------------------------------------------------------------
//Exercise 2
void bar(int value, int width = 40, char fill = '*');

//----------------------------------------------------------------
//Exercise 3
template <typename T>
T clamp_to(T value, T lo, T hi) {
    if (value < lo) {
        return lo;
    }
    if (value > hi) {
        return hi;
    }
    return value;
}

//----------------------------------------------------------------
//Exercise 4
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
void describe(int n) {
    std::println("int {}, {}", n, (n % 2) == 0 ? "even" : "odd");
}

void describe(double x) {
    const bool whole{ std::floor(x) == x };
    std::println("double {}, {}", x, whole ? "whole" : "fractional");
}
void describe(std::string_view s) {
    // starts_with (C++20) tests a prefix; check the five vowels against
    // the front of the string.
    const bool vowel{ s.starts_with('a') || s.starts_with('e') ||
                     s.starts_with('i') || s.starts_with('o') ||
                     s.starts_with('u') };
    std::println("text \"{}\", {} chars, starts with vowel: {}",
        s, s.size(), vowel ? "yes" : "no");
}
//----------------------------------------------------------------
//Exercise 5
int next_roll() {
    static std::default_random_engine engine{ std::random_device{}() };
    static std::uniform_int_distribution<int> die{ 1,6 };
    return die(engine);
}
//----------------------------------------------------------------
//Exercise 6
// Exercise 6a - digit_sum(): recursive
//
// Base case: n < 10 returns n. Step: last digit plus digit_sum of the
// rest. [[nodiscard]] because throwing the result away is always a bug.
//
// Sample output:
//     digit_sum(42)    = 6
//     digit_sum(12345) = 15
//     digit_sum(365)   = 14
//
// Walking digit_sum(365) step by step, since that's one of the sample
// cases. The rule: digit_sum(n) = (n % 10) + digit_sum(n / 10), until
// n < 10, then just return n. Each call peels off the LAST digit
// (n % 10) and recurses on the rest (n / 10).
//
// 1. The calls going "down" (winding up)
//
//     digit_sum(365)
//        n % 10 = 5   <- last digit peeled off
//        n / 10 = 36  -> recurse
//        |
//        +-- digit_sum(36)
//               n % 10 = 6   <- last digit peeled off
//               n / 10 = 3   -> recurse
//               |
//               +-- digit_sum(3)
//                      3 < 10  -> BASE CASE, just return 3
//
//     Each level strips one digit off the right end:
//
//     365  ->  36  ->  3
//       \        \      \
//        5        6      (base case: return 3)
//
// 2. The returns going "up" (unwinding)
//
//     Nothing is added until the base case hits bottom - then each
//     pending "+ digit_sum(...)" gets resolved on the way back up:
//
//     digit_sum(3)   returns 3                         (base case)
//     digit_sum(36)  returns 6 + digit_sum(3)  = 6 + 3  = 9
//     digit_sum(365) returns 5 + digit_sum(36) = 5 + 9  = 14
//
// 3. As a call stack (what's actually sitting in memory mid-recursion)
//
//     push digit_sum(365)   waiting on digit_sum(36), holds "5 + ?"
//          |
//          v
//     push digit_sum(36)    waiting on digit_sum(3), holds "6 + ?"
//          |
//          v
//     push digit_sum(3)  -----> returns 3     (bottom of recursion)
//          |
//          v pop, resolve digit_sum(36)  = 6 + 3 = 9
//          |
//          v pop, resolve digit_sum(365) = 5 + 9 = 14
//          |
//          v pop, caller receives 14
//
// 4. The same shape for digit_sum(42) (the simplest sample), expanded
//
//     digit_sum(42)
//      = 2 + digit_sum(4)      42 % 10 = 2,  42 / 10 = 4
//      = 2 + 4                 4 < 10 -> base case, returns 4
//      = 6
//
//     digit_sum(42) --calls--> digit_sum(4)
//          ^                        |
//          |                        v (base case)
//          +---- 2 + 4 = 6 <------  returns 4
//
// The pattern: the base case (n < 10) is the only place that doesn't
// call itself - without it this recurses forever (stack overflow).
// Every recursive call shrinks the problem (n / 10) so it eventually
// reaches that base case. Nothing is actually added until the deepest
// call returns; the additions happen while the stack unwinds.

//----------------------------------------------------------------
[[nodiscard]] long digit_sum(long n) {
    //Base case
    if (n < 10) {
        return n;
    }
    //Recursive step
    return (n % 10) + digit_sum(n / 10);
}

// ---------------------------------------------------------------------
// Exercise 6b - digit_sum_iterative(): the same result as a loop
//
// One stack frame, an explicit accumulator - the iterative counterpart
// of the recursion above.
//
// Walking digit_sum_iterative(365) - same digit-peeling as the
// recursive version (n % 10 grabs a digit, n /= 10 drops it), but
// instead of stacking up calls, `total` accumulates as we go, and the
// loop condition (n > 0) replaces the base case:
//
//     n = 365, total = 0
//
//     iteration 1:  total += 365 % 10 = 5   -> total = 5
//                   n = 365 / 10 = 36
//
//     iteration 2:  total += 36 % 10 = 6    -> total = 11
//                   n = 36 / 10 = 3
//
//     iteration 3:  total += 3 % 10 = 3     -> total = 14
//                   n = 3 / 10 = 0
//
//     n == 0 -> loop ends, return total = 14
//
// As a table:
//
//     n (before)  |  n % 10  |  total (after)  |  n (after, n /= 10)
//     ------------+----------+-----------------+---------------------
//         365     |    5     |        5        |         36
//          36     |    6     |       11        |          3
//           3     |    3     |       14        |          0   -> stop
//
// No call stack here - just one frame and a variable that grows with
// each pass, which is why this uses O(1) stack space where the
// recursive version uses O(digits) stack frames. Same answer either
// way; this is the trade-off recursion vs. iteration usually comes
// down to.
[[nodiscard]] long digit_sum_iterative(long n) {
    long total{};
    while (n > 0) {
        total += n % 10;
        n /= 10;
    }
    return total;
}


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
    {
        /*
        int low{};
        int high{};
        double mean{};
        stats(samples, low, high, mean);
        std::println("low = {}, high = {}, mean = {}", low, high, mean);
        */
    }


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
    {
        /*
        for (int i{}; i < samples.size(); ++i) {
            bar(samples[i] / 2);
        }
        bar(1000);
        bar(20, 20, '=');
        */
    }


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
    {
        /*
        std::println("clamp_to(120, 0, 100)      ={} ", clamp_to(120, 0, 100));
        std::println("clamp_to(-2.5, 0.0, 1.0)  = {}", clamp_to(-2.5, 0.0, 1.0));
        std::println("std::clamp(120, 0, 100)   = {}", std::clamp(120, 0, 100));
        */
    }


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
                            using s.size() and s.starts_with(...)

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
    {
        /*
        describe(88);
        describe(3.5);
        describe(4.0);
        describe("apple");
        describe("banana");
        */
    }


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
    {
        /*
        std::print("rolls:");
        for (int i{}; i < 8; ++i) {
            std::print(" {}", next_roll());
        }
        std::println("");
        */
    }


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
    {
        /*
        //Sum up the numnbers in samples
        long samples_total{};
        for (int i{}; i < samples.size(); ++i) {
            samples_total += samples[i];
        }
        
        std::println("digit_sum({}) = {} (iterative: {})", 
            42L, digit_sum(42L), digit_sum_iterative(42L));
        std::println("digit_sum({}) = {} (iterative: {})", 
            12345L, digit_sum(12345L), digit_sum_iterative(12345L));
        std::println("digit_sum({}) = {} (iterative: {})", 
            samples_total, digit_sum(samples_total), digit_sum_iterative(samples_total));
        */
    }


    /*
        Exercise 7 - Bringing in the image writing features from the project
        that used FetchContent.

        This one is different from the rest: instead of writing a
        function from scratch, you are going to pull in a small existing
        project as a DEPENDENCY and extend it - which is closer to what
        "using a library" looks like in real code.

        1) Copy image.h and image.cpp from
           06.Functions/xx.xxProjectFetchContent into this folder. Those
           two files already know how to build an image in memory (a
           canvas of pixels), draw a color gradient, draw a border around
           the edge, and save the result as a PNG file. You are not
           rewriting any of that - you are reusing it.

        2) Update THIS folder's CMakeLists.txt so it builds with the new
           files. Copy the FetchContent block from 6.19's CMakeLists.txt
           (it downloads the small stb library that actually writes the
           PNG file to disk), add image.cpp / image.h to the
           add_executable(...) call, and add the
           target_include_directories(...) line so the compiler can find
           stb's header. This is the "wire up the dependency" step - the
           functions in image.h are useless to main.cpp until CMake knows
           to compile and link them in.

        3) Add two new functions to image.h / image.cpp, next to the
           ones that are already there:

               void draw_background(std::vector<std::uint8_t>& pixels,
                                     int width, int height,
                                     std::uint8_t r, std::uint8_t g, std::uint8_t b);

           Fills the ENTIRE canvas with one solid color - loop over every
           x, y and call set_pixel. This is what gives you a plain gray
           background instead of the default black canvas.

               void draw_rectangle(std::vector<std::uint8_t>& pixels,
                                    int width, int height,
                                    int x, int y,
                                    int rect_width, int rect_height,
                                    int thickness,
                                    std::uint8_t r, std::uint8_t g, std::uint8_t b);

           Draws an OUTLINED rectangle: (x, y) is its top-left corner,
           rect_width/rect_height is its size, thickness is how many
           pixels thick the outline is, and r/g/b is the outline color -
           the inside of the rectangle is left untouched.

           Note there are TWO different sizes in this signature, and
           they mean different things: width/height (like every other
           function here) is the size of the WHOLE CANVAS - still needed
           so set_pixel can bounds-check and compute the right index.
           rect_width/rect_height is the size of just this one rectangle
           you are drawing on top of that canvas. A call like
           draw_rectangle(pixels, 400, 300, 100, 100, 120, 80, ...) means
           "on a 400x300 canvas, draw a 120x80 rectangle at (100, 100)."

           Look at how draw_border already does this for the whole
           canvas: it colors a pixel only when it is within `thickness`
           pixels of an edge. draw_rectangle needs the same idea, just
           measured from the rectangle's own four edges instead of the
           canvas's edges, and offset by (x, y) so it can be placed
           anywhere.

        4) In main(), build a 400x300 image:
             - draw_background(...) with a mid gray, e.g. (200, 200, 200)
             - keep calling draw_border(...) exactly as in 6.19, so the
               whole canvas still gets an outer edge
             - call your new draw_rectangle(...) to draw one rectangle
               at position (100, 100), sized 120 x 80, with a visible
               outline thickness (e.g. 4) and any color you like
             - write_png("image.png", ...) to save it, same as 6.19

        Sample output:
            wrote image.png (400 x 300) - gray background with a bordered rectangle
    */
    std::println("\n--- Exercise 7: image project (background + rectangle) ---");
    // TODO
    {
        const int width{ 400 };
        const int height{ 300 };

        auto pixels = make_canvas(width, height);


        // This is where we will draw
        draw_background(pixels, width, height, 200, 200, 200);
        draw_rectangle(pixels, width, height, 100, 100, 120, 80,8, 255, 0, 0);

        if (write_png("image.png", width, height, pixels)) {
            std::println("wrote image.png ({} x {}) - gray background with a bordered rectangle",
                width, height);
        }
        else {
            std::println("could not write image.png");
            return 1;
        }

    }

    return 0;
}


//----------------------------------------------------------------
//Exercise 1
void stats(const std::vector<int>& data,
    int& low, int& high, double& mean) {

    long sum{ 0 };
    low = data[0];
    high = data[0];

    for (int i{ 0 }; i < data.size(); ++i) {

        low = std::min(low, data[i]);
        high = std::max(high, data[i]);
        sum += data[i];
    }

    mean = static_cast<double>(sum) / static_cast<double>(data.size());
}
//----------------------------------------------------------------
//Exercise 2
void bar(int value, int width , char fill ) {
    const int length{ std::clamp(value, 0, width) };
    std::println("{}", std::string(static_cast<std::size_t>(length), fill));
}

//----------------------------------------------------------------
