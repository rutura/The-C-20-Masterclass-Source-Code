#include <print>
#include <string>
#include <string_view>

// std::string_view is a lightweight, read-only "view" into a string's
// characters - it doesn't own or copy the text. For a parameter that only
// needs to read a string, it's a cheaper alternative to taking a
// std::string by value, since no copy of the characters is made.
void printCategoryLabel(std::string_view category) {
    std::println("Category: {}", category);
}

int main() {

    // Works directly with a string literal - no std::string is created at all.
    printCategoryLabel("Food");

    // Also works with an existing std::string - it's viewed, not copied.
    std::string category{"Transport"};
    printCategoryLabel(category);

    return 0;
}
