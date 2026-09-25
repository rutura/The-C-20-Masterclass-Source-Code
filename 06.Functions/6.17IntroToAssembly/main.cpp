#include <print>

// This lecture is about READING, not writing - nothing here needs a new
// keyword. The point is to see what the compiler actually does with code
// you already know, pulled from chapters 3 through 6: a variable, main,
// if, a loop, unsigned wraparound, a function call, a reference
// parameter, inline, constexpr, and recursion.
//
// To follow along: paste one function at a time into godbolt.org (or any
// "Compiler Explorer"), pick a compiler (x86-64 gcc or x86-64 clang -
// this course's Linux containers run both locally too), and set the
// compiler options box to "-O0" first - that keeps the assembly close to
// a literal translation of the source, one idea at a time. NOTES.md
// walks through each function's actual assembly output, gcc vs clang,
// with an MSVC comparison where the two platforms genuinely differ.

// ---------------------------------------------------------------------
// Step 2 - a variable is a slot in memory. Paste just the body into
// Compiler Explorer and watch three "mov"s appear - one per variable.
int rectangle_area() {
    int width{4};
    int height{3};
    int area{width * height};
    return area;
}

// ---------------------------------------------------------------------
// Step 3 - if compiles to a compare + a conditional jump, not a
// dedicated "if" instruction. Look for cmp / jle / jmp / labels.
int pass_or_fail(int score) {
    if (score >= 60) {
        return 1;
    } else {
        return 0;
    }
}

// ---------------------------------------------------------------------
// Step 4 - a loop is the same compare-and-jump as Step 3, aimed
// backwards. Look for a jump straight to the check, then a jump back
// up to the body from the bottom.
int sum_below_five() {
    int total{0};
    for (int i{0}; i < 5; ++i) {
        total += i;
    }
    return total;
}

// ---------------------------------------------------------------------
// Step 5 - unsigned wraparound (see 4.3 / 4.4). Same "sub" instruction
// you would get for a signed int - the CPU has no separate unsigned
// path here, and nothing watches for a negative result going wrong.
unsigned int mistaken_refund() {
    unsigned int points{350u};
    points = points - 400u;   // "should" be -50
    return points;
}

// ---------------------------------------------------------------------
// Step 6 - a plain function call (see 3.3). Arguments travel in
// registers, the answer comes back in one register - call / ret,
// exactly like 6.2's stack-frame diagram.
int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}

// ---------------------------------------------------------------------
// Step 7 - pass by value vs. pass by reference (see 6.8), made literal.
// by_value gets its own 4-byte copy; by_ref gets an 8-byte ADDRESS and
// follows it on every use - watch the extra "load, then dereference"
// steps appear only in the second one.
void add_one_by_value([[maybe_unused]] int n) {
    n += 1;   // changes only this function's own copy - never seen outside it (see 6.16)
}

void add_one_by_ref(int& n) {
    n += 1;
}

// ---------------------------------------------------------------------
// Step 8 - inline (see 6.2). At -O0 the call usually survives. Switch
// to -O2 and cube(3) - a literal argument to a tiny function - collapses
// to a single "mov eax, 27": no call, no multiply, the function itself
// disappears from the output.
inline int cube(int num) {
    return num * num * num;
}

// ---------------------------------------------------------------------
// Step 9 - constexpr (see 6.10). Called with a literal, the entire
// computation happens while the compiler is still running - even at
// -O0, because there is no runtime code generated for it at all.
constexpr int square_ce(int num) {
    return num * num;
}

// ---------------------------------------------------------------------
// Step 10 - recursion (see 6.15). sum_to calls itself: "call sum_to"
// targets the very function currently executing. Every nested call
// gets its own fresh stack frame - its own copy of n - stacked on top
// of the one that called it.
long sum_to(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_to(n - 1);
}

int main() {

    std::println("rectangle_area()      = {}", rectangle_area());
    std::println("pass_or_fail(72)      = {}", pass_or_fail(72));
    std::println("sum_below_five()      = {}", sum_below_five());
    std::println("mistaken_refund()     = {}", mistaken_refund());
    std::println("add_numbers(25, 7)    = {}", add_numbers(25, 7));

    int value{10};
    add_one_by_value(value);
    std::println("after by-value call,  value = {}   (unchanged)", value);
    add_one_by_ref(value);
    std::println("after by-ref call,    value = {}   (changed)", value);

    std::println("cube(3)               = {}", cube(3));

    constexpr int nine{square_ce(3)};   // computed by the compiler, not the CPU
    std::println("square_ce(3)          = {}", nine);

    std::println("sum_to(4)             = {}", sum_to(4));

    return 0;
}
