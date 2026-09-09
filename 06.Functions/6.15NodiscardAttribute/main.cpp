#include <print>

// [[nodiscard]] marks a function whose return value should NOT be
// ignored. If a caller drops the result, the compiler issues a warning.
// Use it when calling the function only for a side effect makes no sense
// - the whole point of the call is the value it hands back.

[[nodiscard]] int add(int a, int b) {
    return a + b;
}

// Also useful on functions that report success/failure or a computed
// resource the caller must handle.
[[nodiscard]] bool is_valid_age(int age) {
    return age >= 0 && age <= 150;
}

int main() {

    int sum{add(3, 4)};                        // result used - fine
    std::println("sum = {}", sum);

    std::println("valid: {}", is_valid_age(42));   // result used - fine

    // add(10, 20);          // <- warning: ignoring the return value of a
    //                       //    [[nodiscard]] function
    // is_valid_age(200);    // <- same warning; the answer was the point

    return 0;
}
