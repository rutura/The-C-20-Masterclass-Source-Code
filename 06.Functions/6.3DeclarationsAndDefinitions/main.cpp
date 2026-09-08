#include <print>

// A function has two parts:
//
//   declaration (prototype)  - the signature only, ending in ';'
//                              tells the compiler the name, parameter
//                              types, and return type
//   definition               - the declaration plus the { body }
//
// The compiler must see a declaration BEFORE the first call. The
// definition can come later in the file (or in another file entirely).

// --- Declarations: everything the caller needs, no body ---
int max_of(int a, int b);
int min_of(int a, int b);
int clamp_to_range(int value, int low, int high);

int main() {

    int x{5};
    int y{12};

    // These calls compile because the declarations above are already in
    // scope, even though the definitions are further down.
    std::println("max_of({}, {}) = {}", x, y, max_of(x, y));
    std::println("min_of({}, {}) = {}", x, y, min_of(x, y));
    std::println("clamp_to_range(42, 0, 20) = {}", clamp_to_range(42, 0, 20));

    return 0;
}

// --- Definitions: the same signatures, now with bodies ---
// The parameter names here don't have to match the declaration's.

int max_of(int a, int b) {
    return a > b ? a : b;
}

int min_of(int a, int b) {
    return a < b ? a : b;
}

int clamp_to_range(int value, int low, int high) {
    if (value < low)  { return low; }
    if (value > high) { return high; }
    return value;
}
