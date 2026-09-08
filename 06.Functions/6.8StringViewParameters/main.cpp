#include <print>
#include <string>
#include <string_view>

// std::string_view is a lightweight, read-only "window" onto a sequence
// of characters that lives somewhere else. It does not own or copy the
// text - it is just a pointer plus a length.
//
// As a parameter type it is the best choice for a function that only
// READS a string: one signature accepts std::string, string literals,
// and substrings, all with no allocation.

void greet(std::string_view name) {
    std::println("Hello, {}! ({} characters)", name, name.length());
}

int main() {

    std::string owned{"Alice"};

    greet(owned);            // from a std::string - no copy
    greet("Bob");            // from a string literal - no temporary std::string
    greet(owned.substr(0, 3)); // substr returns a std::string here; still fine

    // Caveat: a string_view does not keep its underlying text alive.
    // Only use it for parameters (the argument outlives the call), not
    // for storing a view of a string that might be destroyed.

    return 0;
}
