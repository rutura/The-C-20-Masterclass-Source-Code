#include <print>

// This lecture is about READING, not writing - nothing here needs a new
// keyword. The point is to see what the compiler actually does with code
// you already know: a variable, main, a function call, inline, constexpr.
//
// To follow along: paste one piece at a time into godbolt.org (or any
// "Compiler Explorer"), pick a compiler (x86-64 gcc works well), and set
// the compiler options box to "-O0" first - that turns optimisation OFF,
// so the assembly matches the source almost line for line. Later, switch
// to "-O2" and watch entire functions disappear - that is the payoff.

// ---------------------------------------------------------------------
// Step 1 - one function, nothing else. Paste just this into Compiler
// Explorer (no main needed) and look at the assembly pane on the right.
int square(int num) {
    return num * num;
}

// ---------------------------------------------------------------------
// Step 2 - a plain variable. At -O0 this reserves a slot on the stack
// and stores 7 into it - a "mov" instruction, nothing clever yet.
void plain_variable_demo() {
    int lucky_number{7};
    std::println("{}", lucky_number);
}

// ---------------------------------------------------------------------
// Step 3 - inline is a *suggestion*. At -O0 the compiler usually keeps
// the call anyway. Switch to -O2 and the call vanishes: the body is
// pasted straight into the caller (see 6.2's "Call overhead and inline").
inline int cube(int num) {
    return num * num * num;
}

// ---------------------------------------------------------------------
// Step 4 - constexpr can run at COMPILE time when every input is known
// then. Call it with a literal and, at -O2, the *entire computation* is
// gone from main - only the final number remains in the assembly.
constexpr int square_ce(int num) {
    return num * num;
}

int main() {

    plain_variable_demo();

    int result{square(6)};              // a runtime call - argument not known at compile time
    std::println("square(6) = {}", result);

    std::println("cube(3) = {}", cube(3));

    constexpr int nine{square_ce(3)};   // computed by the compiler, not the CPU
    std::println("square_ce(3) = {}", nine);

    return 0;
}
