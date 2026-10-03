#include <print>

// Pass by value vs. pass by reference (see 6.8), made literal. by_value
// gets its own 4-byte copy; by_ref gets an 8-byte ADDRESS and follows
// it on every use - watch the extra "load, then dereference" steps
// appear only in the second one.
void add_one_by_value([[maybe_unused]] int n) {
    n += 1;   // changes only this function's own copy - never seen outside it
}

void add_one_by_ref(int& n) {
    n += 1;
}

int main() {
    int value{10};

    add_one_by_value(value);
    std::println("after by-value call, value = {}   (unchanged)", value);

    add_one_by_ref(value);
    std::println("after by-ref call,   value = {}   (changed)", value);

    return 0;
}

// Try it: paste both functions in together and count the instructions
// in each body - add_one_by_ref needs noticeably more, purely to keep
// following that address.
