module;

#include <vector>

export module recursion;

namespace recursion{

    /*
        This example is simple and readable, but recursion can be inefficient for large n due to repeated calculations. In practice, you should use an iterative solution or memoization for better performance.   
    */
    export constexpr int fibonacci(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    export int fibonacci_memo(int n) {
        static std::vector<int> memo(100, -1); // Initialize with -1 to indicate uncomputed values

        if (n == 0) return 0;
        if (n == 1) return 1;

        if (memo[n] != -1) return memo[n]; // Return memoized value if available

        memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2); // Compute and store the value
        return memo[n];
    }

    export constexpr int fibonacci_iterative(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        int prev = 0, curr = 1, next;
        for (int i = 2; i <= n; ++i) {
            next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }

    //Other popular recursion examples: 
    int factorial(int n) {
        if (n == 0) return 1;
        return n * factorial(n - 1);
    }
    
} // namespace recursion