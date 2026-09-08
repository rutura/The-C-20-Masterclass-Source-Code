#include <print>

// Returning a result:
//   - `return expr;` hands `expr` back to the caller as a copy (return
//     by value). This is the normal, safe way.
//   - Mark a function [[nodiscard]] when ignoring its result is almost
//     certainly a bug - the compiler then warns if a caller drops it.

[[nodiscard]] int add(int a, int b) {
    return a + b;               // a copy of the sum goes back to the caller
}

// DANGER: never return a reference or pointer to a local variable.
// `local` is destroyed when the function returns, leaving a dangling
// reference. Return by value instead (as `add` does).
//
// int& broken() {
//     int local{42};
//     return local;           // local dies here - the reference is invalid
// }

int main() {

    int sum{add(3, 4)};
    std::println("sum = {}", sum);

    // Using the result in place is fine.
    std::println("add(10, 20) * 2 = {}", add(10, 20) * 2);

    // add(1, 2);   // <- [[nodiscard]]: compiler warns, the result is lost

    return 0;
}
