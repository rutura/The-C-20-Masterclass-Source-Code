#include <print>
#include <string>
#include <string_view>

// An ATTRIBUTE is a note to the compiler, written in double square
// brackets: [[name]]. It does not change what the code computes - it
// tells the compiler something about a function, variable, or statement
// so it can warn you (or optimise) more usefully.
//
// This lecture shows the three you will meet most often. Recognise the
// [[...]] syntax and you can look the rest up when you see them.

// ---------------------------------------------------------------------
// [[nodiscard]] - "do not throw this return value away"
// The whole point of the call is the answer. Ignoring it is almost
// always a bug, so the compiler warns.
[[nodiscard]] bool username_is_available(std::string_view name) {
    return !name.empty() && name != "admin" && name != "root";
}

// [[nodiscard]] can carry a reason (C++20); it shows up in the warning.
[[nodiscard("check the result before saving the profile")]]
bool profile_is_complete(std::string_view name, int age) {
    return !name.empty() && age > 0;
}

// ---------------------------------------------------------------------
// [[deprecated]] - "this still works, but stop using it"
// Any use triggers a warning. The message points at the replacement.
[[deprecated("use display_name() instead")]]
std::string full_name(std::string_view first, std::string_view last) {
    return std::string{first} + " " + std::string{last};
}

std::string display_name(std::string_view first, std::string_view last) {
    return std::string{last} + ", " + std::string{first};
}

int main() {

    // ---------------------------------------------------------------------
    // [[maybe_unused]] - "I know this is not used; do not warn me"
    // Handy for a value kept only for debugging, or a parameter a
    // function must accept but does not need.
    [[maybe_unused]] bool verbose_logging{true};

    std::string_view candidate{"neo"};

    if (username_is_available(candidate)) {                 // return value used - fine
        std::println("'{}' is free", candidate);
    }

    std::println("profile complete: {}",
                 profile_is_complete(candidate, 30));       // return value used - fine

    std::println("display name: {}", display_name("Thomas", "Anderson"));

    // Each of these would produce a compiler diagnostic:
    //
    //   username_is_available("trinity");   // warning: [[nodiscard]] result ignored
    //   full_name("Thomas", "Anderson");    // warning: 'full_name' is deprecated:
    //                                       //          use display_name() instead

    // You may also run into these - same idea, a hint to the compiler:
    //   [[fallthrough]]         in a switch, "the missing break here is on purpose"
    //   [[noreturn]]            on a function that never returns (calls exit, throws)
    //   [[likely]] / [[unlikely]]  branch-prediction hint; ignore until you profile

    return 0;
}
