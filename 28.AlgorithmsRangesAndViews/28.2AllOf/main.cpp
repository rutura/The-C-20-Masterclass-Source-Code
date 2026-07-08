#include <print>
#include <algorithm>
#include <vector>

bool is_odd(int n) {
    return n % 2 != 0;
}

int main() {

    std::vector<int> collection{2, 6, 8, 49, 64, 71};

    // std::all_of with a lambda predicate
    if (std::all_of(collection.begin(), collection.end(), [](int i) { return i % 2 == 0; })) {
        std::println("(std::all_of) : All numbers in collection are even");
    } else {
        std::println("(std::all_of) : Not all numbers in collection are even");
    }

    std::println("------");

    // std::any_of with a function object (functor) predicate - useful when
    // the predicate needs to carry its own state, here the divisor.
    class DivisibleBy {
    public:
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; }
    private:
        const int d;
    };

    if (std::any_of(collection.begin(), collection.end(), DivisibleBy(7))) {
        std::println("(std::any_of) : At least one number is divisible by 7");
    } else {
        std::println("(std::any_of) : None of the numbers is divisible by 7");
    }

    std::println("-------");

    // std::none_of with a plain function pointer predicate
    if (std::none_of(collection.begin(), collection.end(), is_odd)) {
        std::println("(std::none_of) : None of the numbers is odd");
    } else {
        std::println("(std::none_of) : At least one number is odd");
    }

    return 0;
}