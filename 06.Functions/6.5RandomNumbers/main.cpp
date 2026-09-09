#include <print>
#include <random>   // C++11 random-number facilities

// Random numbers come from two pieces working together:
//
//   an ENGINE        produces raw random bits
//   a DISTRIBUTION   shapes those bits into the range/shape you want
//
// You call the distribution, passing it the engine, to get one value.

int main() {

    // The engine. Default-constructed, it produces the SAME sequence
    // every run (handy while testing - see the seeding lecture to change
    // that).
    std::default_random_engine engine{};

    // A distribution that yields ints 1..6, each equally likely - a die.
    std::uniform_int_distribution<int> die{1, 6};

    // Roll it ten times.
    std::print("ten rolls: ");
    for (int i{0}; i < 10; ++i) {
        std::print("{} ", die(engine));       // call the distribution with the engine
    }
    std::println("");

    // A different range is just a different distribution.
    std::uniform_int_distribution<int> percent{0, 100};
    std::println("a percent: {}", percent(engine));

    return 0;
}
