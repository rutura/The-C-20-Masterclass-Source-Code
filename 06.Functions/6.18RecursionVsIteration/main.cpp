#include <print>

// The same job - factorial - written both ways.

// Recursive: expresses "n! = n * (n-1)!" directly.
long factorial_recursive(int number) {
    if (number <= 1) {
        return 1;
    }
    return number * factorial_recursive(number - 1);
}

// Iterative: a loop with an accumulator. No function calls stacking up.
long factorial_iterative(int number) {
    long result{1};
    for (int i{2}; i <= number; ++i) {
        result *= i;
    }
    return result;
}

int main() {

    for (int n{0}; n <= 10; ++n) {
        std::println("{:2}!  recursive = {:8}   iterative = {:8}",
                     n, factorial_recursive(n), factorial_iterative(n));
    }

    // Trade-offs:
    //   - iteration is usually faster and uses constant stack space
    //   - recursion can be clearer for problems that are themselves
    //     recursive (trees, divide-and-conquer)
    //   - deep recursion without a base case (or that never nears it)
    //     overflows the call stack - the recursive infinite loop

    return 0;
}
