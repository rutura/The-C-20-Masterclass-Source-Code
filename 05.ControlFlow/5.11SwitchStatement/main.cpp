#include <iostream>
#include <print>

int main() {

    // switch compares one integer (or char, or enum) against a list of
    // constant `case` labels and jumps to the match. It's the natural
    // fit when you're branching on many discrete values of a single
    // expression - clearer than a long else-if ladder doing the same.

    std::print("Enter the end-of-file indicator to stop "
               "(Ctrl+Z then Enter on Windows, Ctrl+D on macOS/Linux).\n");

    int aCount{0};
    int bCount{0};
    int cCount{0};
    int dCount{0};
    int fCount{0};

    std::print("Enter a grade (0-100): ");
    int grade{};

    while (std::cin >> grade) {
        switch (grade / 10) {       // 95 -> 9, 83 -> 8, 100 -> 10, ...
            case 9:                 // both 9 and 10 mean an A, so case 9
            case 10:                // falls through into case 10's body
                ++aCount;
                break;              // break stops the switch here
            case 8:
                ++bCount;
                break;
            case 7:
                ++cCount;
                break;
            case 6:
                ++dCount;
                break;
            default:                // anything not matched above
                ++fCount;
                break;              // optional on the last label, kept for symmetry
        }

        std::print("Enter a grade (0-100): ");
    }

    std::println("\nA: {}\nB: {}\nC: {}\nD: {}\nF: {}",
        aCount, bCount, cCount, dCount, fCount);

    // Two things to remember:
    //  - Without `break`, execution falls through into the next case's
    //    body. That's deliberate for case 9 -> 10 above, but a common
    //    accidental bug elsewhere.
    //  - `case` labels must be compile-time constants, not variables.

    return 0;
}
