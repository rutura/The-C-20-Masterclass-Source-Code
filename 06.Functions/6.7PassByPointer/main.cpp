#include <print>

// Pass by pointer: the parameter is T* - the ADDRESS of the caller's
// variable. Inside, you dereference (*p) to reach or change the value.
//
// A pointer parameter does much the same job as a reference parameter,
// with two differences:
//   - it can be null (no object), so the function can be "optional"
//   - the call site shows &arg, making "this may be modified" visible
// Prefer a reference when the argument is always required; reach for a
// pointer when "no value" is a legitimate case.

void square_in_place(int* n) {
    if (n == nullptr) {          // guard: nothing to work on
        return;
    }
    *n *= *n;                    // follow the pointer, modify the target
}

int main() {

    int value{5};
    std::println("before: value = {}", value);
    square_in_place(&value);     // pass the address
    std::println("after : value = {}", value);   // 25

    square_in_place(nullptr);    // safe - the guard handles it
    std::println("nullptr call did nothing, value still {}", value);

    return 0;
}
