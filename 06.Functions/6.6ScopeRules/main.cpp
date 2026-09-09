#include <print>

// SCOPE = the region of code where a name is visible.
// LIFETIME = how long the object exists.

int high_score{1};   // GLOBAL: visible from here to the end of the file

void tally_round() {
    int high_score{25};   // LOCAL: a fresh scratch value each call, gone on return
    std::println("  tally_round: high_score is {} on entry", high_score);
    ++high_score;
    std::println("  tally_round: high_score is {} on exit", high_score);
}

void grow_combo() {
    static int high_score{50};   // created ONCE, on the first call; kept between calls
    std::println("  grow_combo: high_score is {} on entry", high_score);
    ++high_score;
    std::println("  grow_combo: high_score is {} on exit", high_score);
}

int main() {

    std::println("global high_score in main: {}", high_score);

    int high_score{5};   // LOCAL to main - hides the global inside main
    std::println("main's local high_score: {}", high_score);

    {   // a nested block starts a new scope
        int high_score{7};   // hides both the outer local and the global
        std::println("inner block high_score: {}", high_score);
    }

    std::println("main's local high_score again: {}", high_score);   // back to 5

    tally_round();     // 25 -> 26
    grow_combo();      // 50 -> 51

    tally_round();     // 25 -> 26 again (fresh)
    grow_combo();      // 51 -> 52 (remembered)

    return 0;
}
