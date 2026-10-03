#include <print>

// inline (see 6.2). At -O0 the call usually survives. Switch to -O2
// and cube(3) - a literal argument to a tiny function - collapses to
// a single "mov eax, 27": no call, no multiply, the function itself
// disappears from the output.
inline int cube(int num) {
    return num * num * num;
}

// constexpr (see 6.10). Called with a literal, the entire computation
// happens while the compiler is still running - even at -O0, because
// there is no runtime code generated for it at all.
constexpr int square_ce(int num) {
    return num * num;
}

int main() {
    std::println("cube(3) = {}", cube(3));

    constexpr int nine{square_ce(3)};   // computed by the compiler, not the CPU
    std::println("square_ce(3) = {}", nine);

    return 0;
}

// Try it: flip the compiler options box between -O0 and -O2 on cube
// and watch cube(int) appear and disappear from the output. Then call
// square_ce once with a literal and once with a variable whose value
// the compiler cannot know ahead of time, and compare the two call
// sites' assembly.
