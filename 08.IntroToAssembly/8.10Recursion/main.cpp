#include <print>

// Recursion (see 6.15). sum_to calls itself: "call sum_to" targets the
// very function currently executing. Every nested call gets its own
// fresh stack frame - its own copy of n - stacked on top of the one
// that called it.
long sum_to(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_to(n - 1);
}

int main() {
    std::println("sum_to(4) = {}", sum_to(4));
    return 0;
}

// Try it: paste sum_to in and find the line that reads "call
// sum_to(int)" - a function's assembly containing a call to its own
// name is the tell-tale sign of recursion, visible before you have
// even worked out what the function computes.
