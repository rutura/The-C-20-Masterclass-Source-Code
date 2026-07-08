// Every function template so far has taken a fixed number of type
// parameters. A variadic template takes any number - the mechanism
// std::print/std::format's own {} placeholders are built on, and the
// closing idea for this chapter: template metaprogramming, computing
// something at compile time using the type system itself.

#include <print>
#include <type_traits>

// Args is a "parameter pack" - it stands for zero or more types, deduced
// from however many arguments are actually passed at the call site.
template <typename... Args>
auto sum(Args... args) {
    // A fold expression: (args + ...) expands to
    // (arg1 + (arg2 + (arg3 + ...))) for however many arguments were
    // passed - no manual recursion needed to handle "however many" values.
    return (args + ...);
}

// A fold expression works with any binary operator - not just +.
template <typename... Args>
bool allTrue(Args... args) {
    return (args && ...);
}

template <typename... Args>
void printAll(const Args&... args) {
    // Comma-fold: expands to (std::print(...), std::print(...), ...) -
    // this is how you run a *statement*, rather than compute a value,
    // once per argument in the pack.
    (std::print("{} ", args), ...);
    std::println("");
}

// sizeof...(Args) - a compile-time count of how many types are in the pack,
// no runtime loop needed.
template <typename... Args>
constexpr std::size_t countArgs(Args...) {
    return sizeof...(Args);
}

// A first taste of template metaprogramming: a compile-time computation
// using the type system, not runtime values. This checks - entirely before
// the program ever runs - whether every type in the pack is the same
// arithmetic type, using std::conjunction and std::is_same to combine
// per-type checks into one answer.
template <typename First, typename... Rest>
constexpr bool allSameType = std::conjunction_v<std::is_same<First, Rest>...>;

int main() {

    std::println("sum(1, 2, 3) = {}", sum(1, 2, 3));
    std::println("sum(1.5, 2.5) = {}", sum(1.5, 2.5));
    std::println("sum(1, 2, 3, 4, 5) = {}", sum(1, 2, 3, 4, 5));

    std::println("");
    std::println("allTrue(true, true, true) = {}", allTrue(true, true, true));
    std::println("allTrue(true, false, true) = {}", allTrue(true, false, true));

    std::println("");
    std::print("printAll: ");
    printAll(1, "two", 3.0, 'f');

    std::println("");
    std::println("countArgs(1, 2, 3) = {}", countArgs(1, 2, 3));
    std::println("countArgs() = {}", countArgs());

    std::println("");
    static_assert(allSameType<int, int, int>);
    static_assert(!allSameType<int, double, int>);
    std::println("allSameType checks passed at compile time (static_assert)");

    return 0;
}
