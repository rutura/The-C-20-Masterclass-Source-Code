#include <print>
#include <string>

// const T& - a reference the function promises NOT to modify.
//
// Why not just pass by value? For a big object (a std::string, a large
// struct) a copy is expensive. const T& binds directly to the caller's
// object - no copy - while `const` stops the function from changing it.
// This is the default choice for read-only parameters that aren't tiny.

// By value: every call copies the whole string.
std::size_t length_by_value(std::string text) {
    return text.length();
}

// By const reference: no copy, and `text` cannot be modified here.
std::size_t length_by_const_ref(const std::string& text) {
    // text += "!";   // <- would not compile: text is const
    return text.length();
}

int main() {

    std::string title{"The C++ Masterclass"};

    std::println("by value    : {}", length_by_value(title));
    std::println("by const ref: {}", length_by_const_ref(title));

    // const T& also accepts temporaries and literals directly.
    std::println("literal len : {}", length_by_const_ref("hello"));

    return 0;
}
