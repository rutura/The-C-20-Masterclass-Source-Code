#include <iostream>
#include <print>
#include <random>

// A default engine replays the same sequence every run. To get a
// different sequence each time, SEED the engine.
//
//   - A fixed seed you type in  -> reproducible: same seed, same rolls.
//   - std::random_device        -> a nondeterministic source; use its
//                                  output as the seed for a fresh
//                                  sequence every run.

int main() {

    // Option A: seed from the user - same number reproduces the run.
    std::print("Enter a seed: ");
    unsigned int seed{};
    std::cin >> seed;

    std::default_random_engine seeded_engine{seed};
    std::uniform_int_distribution<int> die{1, 6};

    std::print("rolls for that seed: ");
    for (int i{0}; i < 10; ++i) {
        std::print("{} ", die(seeded_engine));
    }
    std::println("");

    // Option B: random_device gives a real, non-repeating seed.
    std::random_device rd{};
    std::default_random_engine fresh_engine{rd()};   // rd() produces the seed

    std::print("rolls from random_device: ");
    for (int i{0}; i < 10; ++i) {
        std::print("{} ", die(fresh_engine));
    }
    std::println("");

    return 0;
}
