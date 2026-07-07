#include <print>

int main() {

    double amountSpent{93.33};
    double discountRate{0.10};
    std::println("amountSpent (outer) : {}", amountSpent);

    if (amountSpent > 50.0) {
        // This inner amountSpent is a completely different variable that
        // happens to share a name with the outer one - it "shadows" it for
        // the rest of this block. The instant this declaration begins, the
        // name amountSpent refers to the *inner* variable, even inside its
        // own initializer - so it can't be initialized from the outer one
        // just by writing "amountSpent" again, because by then the name no
        // longer means the outer variable. That's why the initializer below
        // reaches for discountRate (still visible, still unambiguous)
        // instead of trying to reuse the shadowed name.
        double amountSpent{100.0 * discountRate}; // a fresh, unrelated value
        std::println("amountSpent (inner, unrelated) : {}", amountSpent);
    }

    // Once the block above closes, the inner amountSpent is gone, and the
    // name refers to the outer one again - completely unaffected by
    // whatever happened inside.
    std::println("amountSpent (outer, after if) : {}", amountSpent);

    // Shadowing like this compiles, but it's a common source of bugs: it's
    // easy to assume you're reading or updating the outer variable when
    // you're actually looking at a shadowed inner one - and, as above, you
    // can't even reuse the outer value to compute the inner one without
    // reaching for a different name. Prefer a distinct name for the inner
    // value instead - it costs nothing and removes the ambiguity entirely.
    std::println("");
    if (amountSpent > 50.0) {
        double discountedAmount{amountSpent * (1.0 - discountRate)}; // clear: reads the outer value by a different name
        std::println("discountedAmount : {}", discountedAmount);
    }
    std::println("amountSpent (unambiguous) : {}", amountSpent);

    return 0;
}
