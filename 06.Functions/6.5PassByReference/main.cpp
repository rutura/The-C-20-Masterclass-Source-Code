#include <print>

// Pass by reference: the parameter (T&) is an ALIAS for the caller's
// variable - not a copy. The function operates on the original, so
// changes are visible after the call returns.

void square_in_place(int& n) {
    n *= n;                      // modifies the caller's variable
}

// A common use: give a function more than one "output" by having it
// write through reference parameters.
void split_seconds(int total, int& minutes, int& seconds) {
    minutes = total / 60;
    seconds = total % 60;
}

int main() {

    int value{4};
    std::println("before: value = {}", value);
    square_in_place(value);
    std::println("after : value = {}", value);   // 16 - the original changed

    int mins{};
    int secs{};
    split_seconds(200, mins, secs);
    std::println("200 seconds = {} min {} sec", mins, secs);

    return 0;
}
