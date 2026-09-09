#include <array>
#include <iostream>
#include <print>
#include <random>

// A fortune-teller SESSION. Two ideas carry it:
//   - a helper FUNCTION, next_fortune(), that does one job: roll a random
//     number, use it to pick a line, hand the line back.
//   - a SCOPED ENUM (enum class) for whether the session is still open.
//
// The player decides WHEN to draw (by typing y); the random number
// decides WHICH fortune comes up.

// A scoped enum: the names live inside Session, so you write
// Session::open, not a bare `open`. It does not implicitly convert to
// int, so it can never be mixed up with a count or a card value.
enum class Session { open, closed };

// Roll once, use the roll to pick a fortune, return it. The engine and
// distribution are `static` so they are built once, not on every call
// (see 6.7) - otherwise every call would restart the same sequence.
std::string_view next_fortune() {
    static constexpr std::array lines{
        "A pleasant surprise is waiting for you.",
        "Now is the time to try something new.",
        "Patience will be rewarded within the week.",
        "An old friend has news you will want to hear.",
        "Trust your first instinct on the next decision.",
        "The obstacle in your path is smaller than it looks.",
    };
    static std::random_device rd{};
    static std::default_random_engine engine{rd()};
    static std::uniform_int_distribution<std::size_t> pick{0, lines.size() - 1};

    return lines[pick(engine)];
}

int main() {

    std::println("Welcome my child.");

    Session session{Session::open};
    while (session == Session::open) {
        std::print("Shall the cards speak? (y/n) ");

        char answer{};
        std::cin >> answer;

        if (answer == 'y' || answer == 'Y') {
            std::println("  The cards say: {}", next_fortune());
        }
        else {
            std::println("Bye!");
            session = Session::closed;
        }
    }

    return 0;
}
