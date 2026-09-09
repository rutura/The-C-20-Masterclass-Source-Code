#include <array>
#include <print>
#include <random>   // C++11 random-number facilities

// Random values come from two pieces working together:
//
//   an ENGINE        produces raw random bits
//   a DISTRIBUTION   shapes those bits into the range/shape you want
//
// You call the distribution, passing it the engine, to get one value.
//
// The running example: a fortune teller. It needs a "random" lucky
// number and a fortune drawn from a fixed list.

int main() {

    // The engine. Default-constructed, it produces the SAME sequence
    // every run - handy while testing a reading, so the fortune does not
    // change from under you. Seeding it (next binary) makes it fresh.
    std::default_random_engine engine{};

    // A distribution that yields ints 1..99, each equally likely - the
    // seeker's lucky number.
    std::uniform_int_distribution<int> lucky_number{1, 99};
    std::println("Your lucky number is {}.", lucky_number(engine));

    // A different range is just a different distribution. Here: an index
    // into the fortunes list below.
    constexpr std::array fortunes{
        "A pleasant surprise is waiting for you.",
        "Now is the time to try something new.",
        "Patience will be rewarded within the week.",
        "An old friend has news you will want to hear.",
        "Trust your first instinct on the next decision.",
    };
    std::uniform_int_distribution<std::size_t> pick{0, fortunes.size() - 1};

    std::println("The cards say: {}", fortunes[pick(engine)]);

    return 0;
}
