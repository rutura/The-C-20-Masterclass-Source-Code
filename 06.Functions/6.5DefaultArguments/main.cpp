#include <print>
#include <string>
#include <string_view>

// A parameter can have a DEFAULT value, used when the caller omits that
// argument. Rules:
//   - defaults go in the PROTOTYPE (the declaration), written once
//   - only TRAILING parameters may have defaults
//   - callers fill arguments left to right; you cannot skip a middle one

std::string greet(std::string_view name,
                  std::string_view greeting = "Hello",
                  char punctuation = '!');   // defaults here, in the declaration

int main() {

    std::println("{}", greet("Sara"));                 // Hello, Sara!
    std::println("{}", greet("Sara", "Welcome"));      // Welcome, Sara!
    std::println("{}", greet("Sara", "Goodbye", '.')); // Goodbye, Sara.

    return 0;
}

// The definition does NOT repeat the defaults.
std::string greet(std::string_view name, std::string_view greeting, char punctuation) {
    return std::string{greeting} + ", " + std::string{name} + punctuation;
}
