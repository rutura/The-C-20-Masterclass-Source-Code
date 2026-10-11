#include <algorithm>
#include <print>
#include <string>
#include <vector>

// A lambda from 6.14 has parameters of fixed types: [](int a, int b) works for
// ints and nothing else. Declaring a parameter with `auto` makes the lambda
// GENERIC: the parameter can be of any type, and the compiler generates a
// version of the lambda for each type it is called with. It is a function
// template, written without the word template.

// The same idea for ordinary functions (C++20): `auto` in the parameter list is
// shorthand for a template. This function:
void print_pair(auto first, auto second) {
    std::println("({}, {})", first, second);
}

// is exactly this one. Each `auto` is a NEW template parameter, so the two
// arguments may have different types.
template <typename T, typename U>
void print_pair_longhand(T first, U second) {
    std::println("({}, {})", first, second);
}

// With `auto` as the result too (16.2), a whole function in one line.
auto sum_of(auto first, auto second) {
    return first + second;
}

int main() {

    std::println("--- a lambda with auto parameters");
    auto show{[](auto value) { std::println("value: {}", value); }};
    show(5);                               // this call makes the version for int
    show(2.5);                             // and this one the version for double
    show(std::string{"north"});            // and this one for std::string

    std::println("\n--- the same idea for functions");
    print_pair(21, 24.5);
    print_pair_longhand(std::string{"south"}, 'S');
    std::println("sum_of(2, 3.5) = {}", sum_of(2, 3.5));

    // One lambda, several container types: it works for anything with a > 10.
    std::println("\n--- one lambda, two element types");
    std::vector<int> counts{4, 12, 7, 30};
    std::vector<double> temperatures{18.5, 24.0, 8.5, 21.5};
    auto above_ten{[](auto value) { return value > 10; }};
    auto many_counts{std::ranges::count_if(counts, above_ten)};
    auto warm_readings{std::ranges::count_if(temperatures, above_ten)};
    std::println("counts above 10: {}   temperatures above 10: {}", many_counts, warm_readings);

    // Captures (6.14) work as before.
    double limit{20.0};
    auto hotter{[limit](auto value) { return value > limit; }};
    std::println("hotter than 20: {} readings", std::ranges::count_if(temperatures, hotter));

    // `auto` takes its argument BY VALUE: a std::string would be copied on every
    // call. Say `const auto&` when the type may be big, as with any parameter.
    std::println("\n--- by value or by reference");
    std::vector<std::string> stations{"north", "south", "east", "west"};
    auto long_name{[](const auto& name) { return name.size() > 4; }};
    std::println("long station names: {}", std::ranges::count_if(stations, long_name));

    // Each type gets its OWN version of the lambda, and so its own `static`
    // variable. Three calls with int, one with double:
    std::println("\n--- one version per type");
    auto count_calls{[](auto) {
        static int calls{0};
        return ++calls;
    }};
    count_calls(1);
    count_calls(2);
    int third{count_calls(3)};
    int first_double{count_calls(1.5)};
    std::println("third call with an int: calls = {}", third);              // 3
    std::println("first call with a double: calls = {}", first_double);     // 1: a separate version

    // When two parameters must be the SAME type, give the lambda an explicit
    // template parameter list (C++20), like a function template:
    std::println("\n--- when the parameters must match");
    auto larger_of{[]<typename T>(T a, T b) { return a < b ? b : a; }};
    std::println("larger_of(3, 8) = {}", larger_of(3, 8));
    // larger_of(3, 8.5);                 // error: T would have to be both int and double

    auto larger_mixed{[](auto a, auto b) { return a < b ? b : a; }};
    // larger_mixed(3, 8.5) compiles, but `a < b ? b : a` has two different
    // types in its branches, so the result is converted to a common type.
    std::println("larger_mixed(3, 8.5) = {}", larger_mixed(3, 8.5));
    return 0;
}
