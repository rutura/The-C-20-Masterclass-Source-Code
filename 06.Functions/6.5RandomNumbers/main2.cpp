#include <array>
#include <iostream>
#include <print>
#include <random>

// A default engine replays the same reading every run. To get a
// different one each time, SEED the engine.
//
//   - A fixed seed the seeker types in -> reproducible: same seed, same
//     fortune. Two people with the same "birth number" get the same
//     reading.
//   - std::random_device -> a nondeterministic source; use its output as
//     the seed for a fresh fortune every run.

int main() {

    constexpr std::array fortunes{
        "A pleasant surprise is waiting for you.",
        "Now is the time to try something new.",
        "Patience will be rewarded within the week.",
        "An old friend has news you will want to hear.",
        "Trust your first instinct on the next decision.",
    };
    std::uniform_int_distribution<std::size_t> pick{0, fortunes.size() - 1};

    // Option A: seed from the seeker - the same number always draws the
    // same fortune.
    unsigned int seed{ 100 };

    std::default_random_engine seeded_engine{seed};
    std::println("For {}, the cards say: {}", seed, fortunes[pick(seeded_engine)]);

    // Option B: random_device gives a real, non-repeating seed - a fresh
    // draw no matter who is asking.
    std::random_device rd{};
    std::default_random_engine fresh_engine{rd()};   // rd() produces the seed

    std::println("And a fresh draw for today: {}", fortunes[pick(fresh_engine)]);

    return 0;
}
