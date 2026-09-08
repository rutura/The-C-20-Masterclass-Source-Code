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
    int failed_attempts{2};
    int minutes_since_reset{40};

    bool locked{failed_attempts >= 3 && minutes_since_reset < 15};
    std::println("\nlocked (too many attempts AND reset too recent): {}", locked);

    bool allow_in{failed_attempts < 3 || minutes_since_reset >= 15};
    std::println("allow_in (few attempts OR enough time passed): {}", allow_in);

    // --- Short-circuit evaluation ---
    // && stops as soon as it sees a false: if `sessions != 0` is false,
    // the right side is never evaluated. Likewise || stops on the first
    // true. This lets you guard a risky check with a cheap one on its
    // left, e.g. `sessions != 0 && total_requests / sessions > threshold`.
    int total_requests{4200};
    int sessions{0};
    bool heavy_user{(sessions != 0) && ((total_requests / sessions) > 100)};   // right side skipped, no divide-by-zero
    std::println("heavy_user (guarded by sessions != 0): {}", heavy_user);

    return 0;
}
