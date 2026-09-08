#include <print>

// A recursive function calls itself. Every recursive function needs:
//   - a BASE CASE that returns without recursing (stops the chain)
//   - a RECURSIVE STEP that calls itself with a "smaller" argument,
//     moving toward the base case

// factorial(n) = n * (n-1) * ... * 1,  with 0! = 1
long factorial(int n) {
    if (n <= 1) {                // base case
        return 1;
    }
    return n * factorial(n - 1); // recursive step
}

// fibonacci(n): 0, 1, 1, 2, 3, 5, 8, ...
long fibonacci(long n) {
    if (n == 0 || n == 1) {      // two base cases
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// The same factorial written as a loop. Iterative code is usually
// faster and uses no call-stack depth; reach for recursion when it
// makes the problem clearer (trees, divide-and-conquer), not by reflex.
long factorial_iterative(int n) {
    long result{1};
    for (int i{2}; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {

    for (int i{0}; i <= 10; ++i) {
        std::println("{:2}! = {}", i, factorial(i));
    }

    std::println("");
    for (int i{0}; i <= 10; ++i) {
        std::println("fibonacci({}) = {}", i, fibonacci(i));
    }

    std::println("");
    std::println("factorial_iterative(10) = {}", factorial_iterative(10));

    return 0;
}
