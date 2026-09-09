#include <print>
#include <random>

// The three-card draw. This binary pulls three things together:
//   - a helper FUNCTION, draw_card(), that does one job and returns a value
//   - a SCOPED ENUM (enum class) for how the reading is going
//   - a switch with an initializer on the first card

// A scoped enum: the names live inside Reading, so you write
// Reading::fortune_favors, not a bare `fortune_favors`. They don't
// implicitly convert to int, which keeps them from being mixed up with
// card values.
enum class Reading { draw_again, fortune_favors, fortune_frowns };

// Draw one card (1..13, as in a suit), announce it, return its value.
int draw_card() {
    static std::random_device rd{};
    static std::default_random_engine engine{rd()};
    static std::uniform_int_distribution<int> card{1, 13};

    const int value{card(engine)};
    std::println("  drew a {}", value);
    return value;
}

int main() {

    Reading reading{Reading::draw_again};
    int sign{0};

    // The first card either settles the reading or becomes the "sign" the
    // seeker must draw again to have the fortune favor them.
    switch (const int first{draw_card()}; first) {
        case 7:
        case 11:
            reading = Reading::fortune_favors;
            break;
        case 1:
        case 13:
            reading = Reading::fortune_frowns;
            break;
        default:
            sign = first;
            std::println("  your sign is {} - draw it again before a 7", sign);
            break;
    }

    // Keep drawing until the sign comes back (favor) or a 7 shows (frown).
    while (reading == Reading::draw_again) {
        if (const int value{draw_card()}; value == sign) {
            reading = Reading::fortune_favors;
        }
        else if (value == 7) {
            reading = Reading::fortune_frowns;
        }
    }

    std::println("{}", reading == Reading::fortune_favors
                           ? "The cards favor you."
                           : "The cards are not with you today.");

    return 0;
}
