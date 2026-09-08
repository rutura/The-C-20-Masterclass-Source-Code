#include <print>

// How an argument reaches a function - the two ways.
//
//   PASS BY VALUE      the parameter is a COPY of the argument.
//                      Changing the parameter does not affect the caller.
//
//   PASS BY REFERENCE  the parameter (written T&) is an ALIAS for the
//                      caller's variable. Changing the parameter changes
//                      the caller's variable.

// By value: `number` is a copy of x. The caller's x is untouched.
int square_by_value(int number) {
    number *= number;
    return number;              // the new value is only visible via the return
}

// By reference: `ref` refers to the caller's variable itself.
void square_by_reference(int& ref) {
    ref *= ref;                 // the caller's variable is modified in place
}

int main() {

    int x{2};
    std::println("x = {} before square_by_value", x);
    std::println("square_by_value(x) returns {}", square_by_value(x));
    std::println("x = {} after square_by_value  (unchanged)\n", x);

    int z{4};
    std::println("z = {} before square_by_reference", z);
    square_by_reference(z);
    std::println("z = {} after square_by_reference  (changed)", z);

    return 0;
}
