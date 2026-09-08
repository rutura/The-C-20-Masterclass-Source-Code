#include <iterator>
#include <print>

// `constexpr` function: CAN run at compile time when its arguments are
// known then. Use it for small pure computations you might want as
// array sizes, template arguments, or just folded into constants.
constexpr int cube(int side) {
    return side * side * side;
}

// `inline` function: the ODR ("one definition rule") relaxation that
// lets a function be defined in a header included by many files without
// a linker error. It is NOT a command to paste the code at the call
// site - the compiler decides that on its own regardless.
inline int twice(int n) {
    return n + n;
}

int main() {

    // Evaluated at compile time - `room` is a genuine compile-time
    // constant, usable where the language requires one.
    constexpr int room{cube(3)};
    int grid[cube(2)]{};         // array size from a constexpr call: 8

    std::println("cube(3) = {}", room);
    std::println("grid has {} elements", std::size(grid));

    // The same constexpr function also works with a run-time value -
    // then it just runs normally at run time.
    int side{4};
    std::println("cube(side) = {}", cube(side));

    std::println("twice(21) = {}", twice(21));

    return 0;
}
