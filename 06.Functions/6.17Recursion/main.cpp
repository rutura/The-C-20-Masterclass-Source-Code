#include <print>

// A RECURSIVE function calls itself. Every one needs:
//   BASE CASE       returns without recursing (stops the chain)
//   RECURSIVE STEP  calls itself with an argument closer to the base case

// factorial(n) = n * (n-1) * ... * 1,  with 0! = 1! = 1
long factorial(int number) {
    if (number <= 1) {                    // base case
        return 1;
    }
    return number * factorial(number - 1);   // recursive step
}

// fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, ...   two base cases
long fibonacci(long number) {
    if (number == 0 || number == 1) {
        return number;
    }
    return fibonacci(number - 1) + fibonacci(number - 2);
}

int main() {

    for (int i{0}; i <= 10; ++i) {
        std::println("{:2}! = {}", i, factorial(i));
    }

    std::println("");

    for (int i{0}; i <= 15; ++i) {
        std::println("fibonacci({:2}) = {}", i, fibonacci(i));
    }

    return 0;
}
