#include <iostream>
#include <print>

int main() {

    // switch compares one integer (or char, or enum) against a list of
    // constant `case` labels and jumps to the match. It's the natural
    // fit when you're branching on many discrete values of a single
    // expression - clearer than a long else-if ladder doing the same.

    std::print("Enter the end-of-file indicator to stop "
               "(Ctrl+Z then Enter on Windows, Ctrl+D on macOS/Linux).\n");

    int oneStar{0};
    int twoStar{0};
    int threeStar{0};
    int fourStar{0};
    int fiveStar{0};

    std::print("Enter a review score (0-100): ");
    int score{};

    while (std::cin >> score) {
        switch (score / 20) {       // 0-19 -> 0, 40-59 -> 2, 100 -> 5, ...
            case 0:
                ++oneStar;
                break;              // break stops the switch here
            case 1:
                ++twoStar;
                break;
            case 2:
                ++threeStar;
                break;
            case 3:
                ++fourStar;
                break;
            case 4:                 // 80-99 and 100 both mean 5 stars, so
            case 5:                 // case 4 falls through into case 5's body
                ++fiveStar;
                break;
            default:                // score outside 0-100
                std::println("  ignoring out-of-range score {}", score);
                break;              // optional on the last label, kept for symmetry
        }

        std::print("Enter a review score (0-100): ");
    }

    std::println("\n1 star : {}\n2 star : {}\n3 star : {}\n4 star : {}\n5 star : {}",
        oneStar, twoStar, threeStar, fourStar, fiveStar);

    // Two things to remember:
    //  - Without `break`, execution falls through into the next case's
    //    body. That's deliberate for case 4 -> 5 above, but a common
    //    accidental bug elsewhere.
    //  - `case` labels must be compile-time constants, not variables.

    return 0;
}
