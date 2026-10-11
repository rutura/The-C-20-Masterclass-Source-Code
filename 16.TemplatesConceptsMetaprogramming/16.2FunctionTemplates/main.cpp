#include <print>
#include <string>
#include <vector>

// 6.13 gave us the first function template: one type parameter, T, deduced
// from the arguments. This lecture goes further, still with functions.

struct Reading {
    double celsius;
};

bool operator<(const Reading& a, const Reading& b) {
    return a.celsius < b.celsius;
}

// ---------------------------------------------------------------------------
// 1. More than one type parameter. The two arguments need not have the same
//    type. The result type is written as `auto`: the compiler works it out
//    from the return statement, here the type of `first + second`.
// ---------------------------------------------------------------------------
template <typename T, typename U>
auto sum_of(T first, U second) {
    return first + second;
}

// ---------------------------------------------------------------------------
// 2. A parameter that cannot be deduced. Nothing in the argument list says what
//    To is, so the caller names it: convert_to<int>(21.7). From is still deduced.
//    Explicit arguments fill the parameters from the left.
// ---------------------------------------------------------------------------
template <typename To, typename From>
To convert_to(From value) {
    return static_cast<To>(value);
}

// ---------------------------------------------------------------------------
// 3. A default for a template parameter. Unless the caller says otherwise, the
//    mean is computed in double. T is deduced from the vector, as in chapter 15.
// ---------------------------------------------------------------------------
template <typename Result = double, typename T>
Result mean_of(const std::vector<T>& values) {
    Result total{};
    for (const T& value : values) {
        total += value;
    }
    return total / static_cast<Result>(values.size());
}

// ---------------------------------------------------------------------------
// 4. A template and an ordinary function with the same name.
// ---------------------------------------------------------------------------
void describe(int value) {
    std::println("  the ordinary function for int: {}", value);
}

template <typename T>
void describe(T value) {
    std::println("  the template: {}", value);
}

// ---------------------------------------------------------------------------
// 5. A template works for every type that supports what its body does.
// ---------------------------------------------------------------------------
template <typename T>
T larger_of(T a, T b) {
    return a < b ? b : a;
}

int main() {

    std::println("--- 1. two type parameters, and auto as the result");
    std::println("sum_of(2, 3)        = {}", sum_of(2, 3));                     // T = int, U = int: an int
    std::println("sum_of(2, 3.5)      = {}", sum_of(2, 3.5));                   // an int plus a double is a double
    std::println("sum_of(string, \"!\") = {}", sum_of(std::string{"north"}, "!"));   // string + const char*

    std::println("\n--- 2. naming a parameter that cannot be deduced");
    std::println("convert_to<int>(21.7)    = {}", convert_to<int>(21.7));       // To = int (named), From = double (deduced)
    std::println("convert_to<double>(21)   = {}", convert_to<double>(21));
    // convert_to(21.7);                    // error: nothing says what To is

    std::println("\n--- 3. a default template argument");
    std::vector<int> counts{1, 2, 4};
    std::println("mean_of(counts)          = {}", mean_of(counts));             // Result = double by default
    std::println("mean_of<int>(counts)     = {}", mean_of<int>(counts));        // Result named: integer division
    std::println("mean_of<float>(counts)   = {}", mean_of<float>(counts));

    std::println("\n--- 4. template versus ordinary function");
    describe(5);                  // both fit equally well: the ordinary function wins
    describe(5.5);                // only the template fits without a conversion
    describe('x');                // char matches the template exactly; the function would need a conversion
    describe<int>(7);             // asking for the template by name

    std::println("\n--- 5. any type that supports <");
    std::println("larger_of(3, 8)                = {}", larger_of(3, 8));
    std::println("larger_of(18.5, 24.0)           = {}", larger_of(18.5, 24.0));
    std::println("larger_of(\"north\", \"south\") as strings = {}", larger_of(std::string{"north"}, std::string{"south"}));
    std::println("larger_of(Reading, Reading)     = {}", larger_of(Reading{18.5}, Reading{24.0}).celsius);

    // A type without < compiles until the template body needs it:
    //     struct Marker {};
    //     larger_of(Marker{}, Marker{});     // error, reported INSIDE larger_of, at `a < b`
    // 16.7 shows how a template can state what it needs, so that the error
    // appears at the call, in plain words.
    return 0;
}
