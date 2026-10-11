#include <cstddef>
#include <print>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

// A template says what to do for ANY type. Sometimes one type deserves
// something different. Two tools for that: SPECIALIZATION (a separate
// definition for particular types) and `if constexpr` (a branch chosen while
// compiling).

// ---------------------------------------------------------------------------
// 1. Full specialization: a definition for exactly one type.
//    The general template, the "primary":
// ---------------------------------------------------------------------------
template <typename T>
struct Label {
    static constexpr std::string_view text{"a value"};
};

//    and a specialization for double. `template <>` means "no parameters left
//    to fill": this is the complete answer for Label<double>.
template <>
struct Label<double> {
    static constexpr std::string_view text{"degrees"};
};

template <>
struct Label<int> {
    static constexpr std::string_view text{"a count"};
};

// ---------------------------------------------------------------------------
// 2. Partial specialization: a definition for a whole FAMILY of types, a
//    pattern with some parameters still open.
// ---------------------------------------------------------------------------
template <typename T>
struct Label<std::vector<T>> {                       // a vector of anything
    static constexpr std::string_view text{"a list"};
};

template <typename T>
struct Label<T*> {                                   // a pointer to anything
    static constexpr std::string_view text{"an address"};
};

// ---------------------------------------------------------------------------
// 3. if constexpr: the branch is chosen at compile time, and the branches that
//    are not chosen are NOT COMPILED for this T. That is what makes it more than
//    a plain `if`.
// ---------------------------------------------------------------------------
template <typename T>
std::string describe(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "whole number " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "fraction " + std::to_string(value);
    } else if constexpr (requires { value.size(); }) {      // a requires expression (16.8) as the test
        return "something with " + std::to_string(value.size()) + " elements";
    } else {
        return "something else";
    }
}

// The same function with a plain `if` would not compile for an int, because
// the compiler would still check the branch that calls value.size():
//
//     if (std::is_integral_v<T>) { ... } else { return std::to_string(value.size()); }
//                                                                    ^^^^^ error for T = int

// if constexpr also removes work: the unused branch generates no code at all.
template <typename T>
T twice_or_negated(T value) {
    if constexpr (std::is_unsigned_v<T>) {
        return value * 2;                            // negating an unsigned value is meaningless: it wraps around
    } else {
        return -value;
    }
}

struct Marker {};

int main() {

    std::println("--- a specialization per type");
    std::println("Label<int>    : {}", Label<int>::text);
    std::println("Label<double> : {}", Label<double>::text);
    std::println("Label<char>   : {}", Label<char>::text);                   // no specialization: the general one

    std::println("\n--- a partial specialization for a family");
    std::println("Label<std::vector<int>>    : {}", Label<std::vector<int>>::text);
    std::println("Label<std::vector<double>> : {}", Label<std::vector<double>>::text);
    std::println("Label<int*>                : {}", Label<int*>::text);
    std::println("Label<std::string>         : {}", Label<std::string>::text);

    std::println("\n--- if constexpr");
    std::println("{}", describe(42));
    std::println("{}", describe(21.5));
    std::println("{}", describe(std::string{"north"}));
    std::println("{}", describe(std::vector<int>{1, 2, 3}));
    std::println("{}", describe(Marker{}));

    std::println("\ntwice_or_negated(21)    = {}", twice_or_negated(21));
    std::println("twice_or_negated(21u)   = {}", twice_or_negated(21u));

    // You have written specializations already, by recipe:
    //   template <> struct std::formatter<Wind> { ... }       (12.4)
    //   template <> struct std::hash<GridCell> { ... }        (14.7)
    // Each says: "for THIS type, the standard template should do the following".
    // The primary templates std::formatter and std::hash are declared in the
    // library; yours are specializations of them.
    //
    // Which tool?
    //   a different class or constant for particular types          specialization
    //   one function, small differences inside                      if constexpr
    //   different functions, chosen by what a type can do           overloads with concepts (16.7)
    // A FUNCTION template cannot be partially specialized; write overloads instead.
    return 0;
}
