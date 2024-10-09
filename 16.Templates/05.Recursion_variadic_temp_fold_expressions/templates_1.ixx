/*
    . Exploring template recursion
        . bare recursion function that executes at run time
        . template recursion that executes at compile time
        . constexpr function that computes the factorial of a number at compile time
*/
module;

export module templates_1;

namespace templates_1{

    //Bare recursion
    export int factorial_bare(int n) {
        if (n <= 1) return 1;
        return n * factorial_bare(n - 1);
    }

    // Template recursion - primary template
    export template<int N>
    struct Factorial {
        static constexpr int value = N * Factorial<N - 1>::value;
    };

    // Specialization for the base case
    template<>
    struct Factorial<0> {
        static constexpr int value = 1;
    };


    //constexpr function
    export constexpr int factorial(int n) {
        return (n <= 1) ? 1 : (n * factorial(n - 1));
    }
    
} // namespace templates_1