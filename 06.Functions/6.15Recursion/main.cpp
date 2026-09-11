#include <print>

// A RECURSIVE function calls itself. Every one needs:
//   BASE CASE       returns without recursing (stops the chain)
//   RECURSIVE STEP  calls itself with an argument closer to the base case

// sum_to(n) = n + (n-1) + ... + 1 + 0
long sum_to(int n) {
    if (n <= 0) {                 // base case
        return 0;
    }
    return n + sum_to(n - 1);     // recursive step: n, then the rest
}

// The same job as a loop - one stack frame, an accumulator instead of
// pending "n + ..." additions.
long sum_to_iterative(int n) {
    long total{0};
    for (int i{1}; i <= n; ++i) {
        total += i;
    }
    return total;
}

// fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, ...  TWO recursive calls per step,
// so the call tree fans out - fibonacci(n) makes ~2^n calls. Fine for
// small n here; try n = 40 and feel it crawl.
long fibonacci(long n) {
    if (n == 0 || n == 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

    for (int n{0}; n <= 10; ++n) {
        std::println("sum_to({:2}) = {:3}   (loop: {})",
                     n, sum_to(n), sum_to_iterative(n));
    }

    std::println("");

    for (int n{0}; n <= 15; ++n) {
        std::println("fibonacci({:2}) = {}", n, fibonacci(n));
    }

    return 0;
}
