#include <print>
#include <random>

// Craps, simplified. This lecture pulls three things together:
//   - a helper FUNCTION, roll_dice(), that does one job and returns a value
//   - a SCOPED ENUM (enum class) for the game's status
//   - a switch with an initializer on the first roll

// A scoped enum: the names live inside Status, so you write
// Status::won, not a bare `won`. They don't implicitly convert to int,
// which keeps them from being mixed up with other values.
enum class Status { keep_rolling, won, lost };

// roll two dice, print them, return the sum.
int roll_dice() {
    static std::random_device rd{};
    static std::default_random_engine engine{rd()};
    static std::uniform_int_distribution<int> die{1, 6};

    const int d1{die(engine)};
    const int d2{die(engine)};
    std::println("  rolled {} + {} = {}", d1, d2, d1 + d2);
    return d1 + d2;
}

int main() {

    Status status{Status::keep_rolling};
    int point{0};

    // First roll decides the game or sets the "point".
    switch (const int first{roll_dice()}; first) {
        case 7:
        case 11:
            status = Status::won;
            break;
        case 2:
        case 3:
        case 12:
            status = Status::lost;
            break;
        default:
            point = first;
            std::println("  point is {}", point);
            break;
    }

    // Keep rolling until you hit the point (win) or a 7 (lose).
    while (status == Status::keep_rolling) {
        if (const int sum{roll_dice()}; sum == point) {
            status = Status::won;
        }
        else if (sum == 7) {
            status = Status::lost;
        }
    }

    std::println("{}", status == Status::won ? "You win!" : "You lose.");

    return 0;
}
