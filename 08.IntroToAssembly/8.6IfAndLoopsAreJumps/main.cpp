#include <print>

// if compiles to a compare + a conditional jump, not a dedicated "if"
// instruction. Look for cmp / jle / jmp / labels.
int pass_or_fail(int score) {
    if (score >= 60) {
        return 1;
    } else {
        return 0;
    }
}

// A loop is the same compare-and-jump as above, aimed backwards. Look
// for a jump straight to the check, then a jump back up to the body
// from the bottom.
int sum_below_five() {
    int total{0};
    for (int i{0}; i < 5; ++i) {
        total += i;
    }
    return total;
}

int main() {
    std::println("pass_or_fail(72) = {}", pass_or_fail(72));
    std::println("sum_below_five() = {}", sum_below_five());
    return 0;
}

// Try it: change ">= 60" to "> 60" in pass_or_fail and try to make
// sense of the generated assembly. Then change the for loop in
// sum_below_five to an equivalent while loop and compare - the
// assembly should end up nearly identical, because for and while are
// the same loop, just spelled differently in C++ source.
