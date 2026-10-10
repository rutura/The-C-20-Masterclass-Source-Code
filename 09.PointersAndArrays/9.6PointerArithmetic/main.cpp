#include <cstddef>
#include <cstdint>
#include <print>

// A pair of pointers is a way to describe a run of elements: from "first"
// up to, but not including, "last". Remember this shape. In chapters 14 and
// 15 it comes back as the iterator pair every standard algorithm takes.
int sum(const int* first, const int* last) {
    int total{0};
    for (const int* p{first}; p != last; ++p) {
        total += *p;
    }
    return total;
}

int main() {

    int readings[5]{68, 71, 69, 72, 70};
    const int* first{readings};

    // Adding 1 to a pointer moves it by one ELEMENT, not by one byte. The
    // compiler multiplies by sizeof(int) for you. This is the
    // [rdi + rcx*4] you wrote by hand in 8.12.
    const int* second{first + 1};

    auto first_address{reinterpret_cast<std::uintptr_t>(first)};
    auto second_address{reinterpret_cast<std::uintptr_t>(second)};
    std::println("first + 1 is {} bytes after first (sizeof(int) = {})",
                 second_address - first_address, sizeof(int));

    // Indexing is pointer arithmetic with a nicer face:
    // first[3] means exactly *(first + 3).
    std::println("*(first + 3) = {}, first[3] = {}", *(first + 3), first[3]);

    // The "end" pointer: ONE PAST the last element. Forming it is allowed,
    // dereferencing it is not. It exists so that "first != last" is the test
    // for "still inside", even for an empty run (first == last).
    const int* const last{readings + 5};

    std::print("\nwalking forward:  ");
    for (const int* p{first}; p != last; ++p) {
        std::print("{} ", *p);
    }

    std::print("\nwalking backward: ");
    for (const int* p{last}; p != first;) {
        --p;                                // step first, then read
        std::print("{} ", *p);
    }
    std::println("");

    // Subtracting two pointers into the same array gives the number of
    // elements between them, as a signed std::ptrdiff_t.
    std::ptrdiff_t count{last - first};
    std::println("\nlast - first = {} elements", count);
    std::println("sum(first, last)     = {}", sum(first, last));

    // Any sub-range works, because a range is just two pointers.
    std::println("sum of the middle three = {}", sum(first + 1, first + 4));

    // Pointers into the same array can be compared with <, <=, >, >=.
    std::println("first < last: {}", first < last);

    // The rules, all of which are undefined behaviour when broken, even if
    // you never dereference the result:
    //   first + 6                  more than one past the end
    //   first - 1                  before the start
    //   &a_different_array - first subtracting pointers into different arrays
    // The compiler will not stop you. Sanitizers will (see the project).

    return 0;
}
