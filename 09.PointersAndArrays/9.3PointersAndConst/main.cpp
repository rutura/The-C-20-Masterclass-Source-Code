#include <print>

// A pointer has TWO things that could be const: the data it points at, and
// the pointer itself. The compiler lets you choose each one separately.
//
// Read a declaration from the NAME outwards, right to left:
//     const int* p        p is a pointer to an int that is const
//     int* const p        p is a const pointer to an int
//     const int* const p  p is a const pointer to a const int
void print_reading(const int* reading) {
    // A pointer to const is a promise: "I only look, I never write".
    // Writing here, *reading = 0, would not compile.
    std::println("reading is {}", *reading);
}

int main() {

    int reading{72};
    int other{60};

    // 1. non-const pointer, non-const data: free to do both.
    int* free_pointer{&reading};
    *free_pointer = 73;             // change the data
    free_pointer = &other;          // change where it points
    std::println("free_pointer now sees {}", *free_pointer);

    // 2. pointer to const data: can move, cannot write through it.
    const int* read_only_view{&reading};
    read_only_view = &other;        // fine
    // *read_only_view = 0;         // error: the data is const through this pointer
    std::println("read_only_view sees {}", *read_only_view);

    // 3. const pointer: fixed to one object, but that object can change.
    int* const fixed_pointer{&reading};
    *fixed_pointer = 74;            // fine
    // fixed_pointer = &other;      // error: a const pointer cannot be repointed
    std::println("fixed_pointer sees {}", *fixed_pointer);

    // 4. const pointer to const data: neither can change.
    const int* const locked{&reading};
    // *locked = 0;                 // error
    // locked = &other;             // error
    std::println("locked sees {}", *locked);

    // The most common rule in practice: a function that only reads through a
    // pointer takes const T*. It then accepts both const and non-const data.
    print_reading(&reading);

    const int freezing{32};
    print_reading(&freezing);

    // The other direction is not allowed. A pointer to non-const data could
    // be used to change something that was declared const.
    // int* sneaky{&freezing};      // error: cannot convert const int* to int*
    // Casting the const away compiles, but writing through the result is
    // undefined behaviour when the object really was const. Do not do it.

    // const on a pointer to const is a restriction on the VIEW, not on the
    // data. reading itself is not const, so it can still change, and every
    // view of it sees the new value.
    const int* view_of_reading{&reading};
    reading = 80;
    std::println("\nreading was changed directly, view_of_reading now sees {}", *view_of_reading);

    return 0;
}
