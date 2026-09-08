#include <print>

int main() {

    // --- Truth tables: combine bools with && , || , ! ---
    std::println("Logical AND (&&) - true only when BOTH sides are true");
    std::println("false && false : {}", false && false);
    std::println("false && true  : {}", false && true);
    std::println("true  && false : {}", true && false);
    std::println("true  && true  : {}", true && true);

    std::println("\nLogical OR (||) - true when EITHER side is true");
    std::println("false || false : {}", false || false);
    std::println("false || true  : {}", false || true);
    std::println("true  || false : {}", true || false);
    std::println("true  || true  : {}", true || true);

    std::println("\nLogical NOT (!) - flips true and false");
    std::println("!false : {}", !false);
    std::println("!true  : {}", !true);

    // --- Combining conditions in a real check ---
    int grade{72};
    int attendance_pct{80};

    bool passes{grade >= 60 && attendance_pct >= 75};
    std::println("\npasses (grade AND attendance): {}", passes);

    bool needs_review{grade < 60 || attendance_pct < 50};
    std::println("needs_review (grade OR attendance): {}", needs_review);

    // --- Short-circuit evaluation ---
    // && stops as soon as it sees a false: if `grade >= 0` is false, the
    // right side is never evaluated. Likewise || stops on the first true.
    // This lets you guard a risky check with a cheap one on its left,
    // e.g. `count != 0 && total / count > threshold`.
    int count{0};
    bool safe{(count != 0) && ((100 / count) > 10)};   // right side skipped, no divide-by-zero
    std::println("safe (guarded by count != 0): {}", safe);

    return 0;
}
