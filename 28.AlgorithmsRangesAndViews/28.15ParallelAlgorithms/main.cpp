#include <algorithm>
#include <execution>
#include <print>
#include <vector>

int main() {

    // Every algorithm from this chapter has an overload that accepts an
    // execution policy as its first argument, hinting that the standard
    // library is free to run it across multiple threads instead of a single
    // one. std::execution::par asks for that; the implementation is still
    // allowed to run serially if it decides threading isn't worthwhile for
    // this call - the policy is a permission, not a guarantee.
    std::vector<int> numbers{5, 3, 8, 1, 9, 2, 7, 4, 6, 0};

    std::print("numbers(before sort) : ");
    for (auto n : numbers) std::print("{} ", n);
    std::println("");

    std::sort(std::execution::par, numbers.begin(), numbers.end());

    std::print("numbers(after parallel sort) : ");
    for (auto n : numbers) std::print("{} ", n);
    std::println("");

    // std::execution::par_unseq additionally allows the standard library to
    // vectorize (SIMD) within each thread - a stronger hint, but it comes
    // with a matching restriction: the function passed in must not do
    // anything that would break under out-of-order or interleaved
    // execution (no synchronization, no throwing across elements).
    std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> output(input.size());

    std::transform(std::execution::par_unseq, input.begin(), input.end(), output.begin(),
                    [](int n) { return n * n; });

    std::print("squares : ");
    for (auto n : output) std::print("{} ", n);
    std::println("");

    return 0;
}
