#include <print>

int main() {

    // A pointer is an ordinary variable whose VALUE is an address (8.2, 8.5).
    // The type int* reads "pointer to int": it holds the address of a place
    // that holds an int. The & operator asks "where does this variable live?".
    int reading{72};
    int* where{&reading};

    // std::println only knows how to print a pointer as a void*: an address
    // with no type attached. Convert first, then print.
    std::println("reading lives at   {}", static_cast<const void*>(&reading));
    std::println("where holds        {}", static_cast<const void*>(where));
    std::println("where itself is at {}", static_cast<const void*>(&where));

    // In an expression, * means "follow the address": it is the object the
    // pointer points at. Reading and writing through it reach the original.
    std::println("\nreading = {}, *where = {}", reading, *where);

    *where = 75;
    std::println("after *where = 75: reading = {}", reading);

    // The pointer is its own variable, so it can be pointed somewhere else.
    // Nothing changes about the old target.
    int other{60};
    where = &other;
    std::println("after where = &other: *where = {}, reading = {}", *where, reading);

    // Every pointer is the same size, because every address is. The size of
    // what it points to is a property of the TYPE, which is why a pointer to
    // double cannot be used as a pointer to int.
    double temperature{21.5};
    double* temperature_where{&temperature};
    std::println("\nsizeof(int*) = {}, sizeof(double*) = {}",
                 sizeof(where), sizeof(temperature_where));
    std::println("sizeof(*where) = {}, sizeof(*temperature_where) = {}",
                 sizeof(*where), sizeof(*temperature_where));

    // nullptr means "points at nothing". A pointer you have no object for yet
    // should hold it, never a leftover or random address.
    int* nothing{nullptr};

    if (nothing == nullptr) {
        std::println("\nnothing points nowhere");
    }

    // A pointer converts to bool: false for nullptr, true for anything else.
    // Check before every dereference when the pointer might be empty.
    if (nothing) {
        std::println("this never prints: *nothing = {}", *nothing);
    }
    else {
        std::println("not dereferencing it: there is nothing to read");
    }

    // *nothing, with nothing == nullptr, is undefined behaviour: usually an
    // immediate crash, but the standard promises nothing.

    // Gotcha: the * belongs to the NAME, not to the type. In this one
    // declaration only the first variable is a pointer. The second is a
    // plain int, even though it looks like it shares the int*.
    int* first{&reading}, second{5};
    std::println("\nsizeof(first) = {}, sizeof(second) = {}", sizeof(first), sizeof(second));

    // Declare one variable per declaration and the confusion cannot happen.
    return 0;
}
