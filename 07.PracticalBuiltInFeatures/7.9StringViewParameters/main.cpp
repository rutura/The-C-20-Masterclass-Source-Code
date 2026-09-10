#include <print>
#include <string>
#include <string_view>

// std::string_view is a lightweight "look at this text" handle: a pointer
// to characters plus a length. It does not own the characters and does
// not copy them. Use it for read-only string parameters so the function
// accepts std::string, string literals, and substrings without any of
// them being copied.

// Old habit: const std::string&. Passing a string literal to it builds a
// temporary std::string. string_view takes the literal as-is.
std::size_t count_vowels(std::string_view text) {
    constexpr std::string_view all_vowels{"aeiouAEIOU"};
    std::size_t vowels{0};
    for (char c : text) {
        if (all_vowels.find(c) != std::string_view::npos) {
            ++vowels;
        }
    }
    return vowels;
}

// A view can be narrowed cheaply - substr() on a string_view returns
// another view into the *same* characters, no allocation.
std::string_view trim(std::string_view text) {
    while (!text.empty() && text.front() == ' ') {
        text.remove_prefix(1);
    }
    while (!text.empty() && text.back() == ' ') {
        text.remove_suffix(1);
    }
    return text;
}

int main() {
    std::string owned{"programming"};
    std::println("vowels in std::string : {}", count_vowels(owned));
    std::println("vowels in literal      : {}", count_vowels("hello world"));
    std::println("vowels in substring    : {}", count_vowels(std::string_view{owned}.substr(0, 4)));

    std::string padded{"   spaced out   "};
    std::string_view tight{trim(padded)};
    std::println("trimmed: \"{}\" (len {})", tight, tight.size());

    // The pitfall: a string_view is only valid while the characters it
    // points at are alive. Never return a view of a local string or of a
    // temporary - the storage is gone the moment the function returns.
    //
    //   std::string_view broken() {
    //       std::string local{"gone soon"};
    //       return local;          // DANGLING: local dies here
    //   }
    //
    // Rule of thumb: string_view for parameters, std::string when you
    // need to own or outlive the text.
    std::string first{"Ada"};
    std::string last{"Lovelace"};
    std::string full{first + " " + last};        // own the joined result
    std::string_view view_ok{full};              // fine: full outlives view_ok
    std::println("full name: {}", view_ok);

    return 0;
}
