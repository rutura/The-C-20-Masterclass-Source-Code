module;

export module recursion;

namespace recursion{

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

}