#include <concepts>
#include <iterator>
#include <list>
#include <print>
#include <ranges>
#include <string>
#include <vector>

// In 16.2, larger_of(Marker{}, Marker{}) failed with an error inside the body
// of the template. The template NEEDED a type with `<`, but nothing in its
// declaration said so. A CONCEPT is a name for a requirement on a type, and a
// template can state its requirements up front.
//
// A concept is a compile-time yes or no about a type, like the traits of 16.6,
// but meant to be written in the template's declaration. The standard library
// has dozens, in <concepts>, <iterator> and <ranges>.

struct Marker {};                          // no operator<

// ---------------------------------------------------------------------------
// Three ways to write the same requirement: "T can be ordered with < > <= >=".
// ---------------------------------------------------------------------------

// 1. In the template header, in place of `typename`.
template <std::totally_ordered T>
T larger_of(T a, T b) {
    return a < b ? b : a;
}

// 2. With a requires clause after the header.
template <typename T>
    requires std::totally_ordered<T>
T smaller_of(T a, T b) {
    return b < a ? b : a;
}

// 3. With the concept in front of `auto` (16.3): the shortest form.
auto clamp_low(std::totally_ordered auto value, std::totally_ordered auto floor) {
    return value < floor ? floor : value;
}

// ---------------------------------------------------------------------------
// A requires clause can also follow the parameter list of a MEMBER function, to
// restrict that one function. The class works for every T; larger() exists
// only for a T that can be ordered. (The project's Matrix uses this.)
// ---------------------------------------------------------------------------
template <typename T>
class Pair {
public:
    Pair(T first, T second) : first_{first}, second_{second} {}

    T larger() const
        requires std::totally_ordered<T>
    {
        return first_ < second_ ? second_ : first_;
    }

private:
    T first_;
    T second_;
};

// ---------------------------------------------------------------------------
// Constraints choose between overloads.
// ---------------------------------------------------------------------------
void describe(std::integral auto value) {
    std::println("  {} is a whole number", value);
}

void describe(std::floating_point auto value) {
    std::println("  {} is a fraction", value);
}

void describe(const std::string& value) {
    std::println("  '{}' is text", value);
}

// ---------------------------------------------------------------------------
// Concepts for ranges and for callables.
// ---------------------------------------------------------------------------

// Any range (a vector, a list, a view ...) whose elements can be added up.
template <std::ranges::input_range R>
double total_of(const R& values) {
    double total{0.0};
    for (const auto& value : values) {
        total += value;
    }
    return total;
}

// A callable that can be called with a double (6.14, 15.8).
template <std::invocable<double> F>
double apply_to_each(const std::vector<double>& values, F function) {
    double total{0.0};
    for (double value : values) {
        total += function(value);
    }
    return total;
}

int main() {

    std::println("--- constraints on a function template");
    std::println("larger_of(3, 8)              = {}", larger_of(3, 8));
    std::println("larger_of(\"a\", \"b\") strings  = {}", larger_of(std::string{"north"}, std::string{"south"}));
    std::println("smaller_of(2.5, 1.5)         = {}", smaller_of(2.5, 1.5));
    std::println("clamp_low(18, 20)            = {}", clamp_low(18, 20));
    // larger_of(Marker{}, Marker{});
    //   error: no matching function for call to 'larger_of(Marker, Marker)'
    //          constraints not satisfied ... 'Marker' does not satisfy 'totally_ordered'
    //   (that is Clang's wording; GCC lists the same chain as "required for the
    //   satisfaction of 'totally_ordered<T>' [with T = Marker]")
    // The error now names the CALL and the requirement, not a line inside the template.

    std::println("\n--- a constraint on one member function");
    Pair numbers{3, 8};                                  // Pair<int>
    std::println("Pair{{3, 8}}.larger() = {}", numbers.larger());
    Pair<Marker> markers{Marker{}, Marker{}};            // fine: the class itself has no requirement
    // markers.larger();                                 // error: the constraint of larger() is not satisfied

    std::println("\n--- overloads chosen by constraint");
    describe(42);
    describe(21.5);
    describe(std::string{"north"});

    std::println("\n--- a concept for any range of numbers");
    std::vector<double> temperatures{18.5, 24.0, 21.5};
    std::list<int> counts{4, 12, 7};
    std::println("total_of(vector<double>) = {}", total_of(temperatures));
    std::println("total_of(list<int>)      = {}", total_of(counts));
    std::println("total_of(iota(1, 5))     = {}", total_of(std::views::iota(1, 5)));
    // total_of(5);                            // error: 'int' does not satisfy 'input_range'

    std::println("\n--- a concept for a callable");
    double doubled{apply_to_each(temperatures, [](double value) { return value * 2.0; })};
    std::println("sum of doubled temperatures = {}", doubled);
    // apply_to_each(temperatures, 5);         // error: constraints not satisfied: an int cannot be called with a double

    // A concept is a bool known at compile time, so it works in a static_assert
    // exactly like a trait (16.6). This is what the assertions of 14.2 were:
    std::println("\n--- asking a concept directly");
    static_assert(std::forward_iterator<std::list<int>::iterator>);
    static_assert(!std::random_access_iterator<std::list<int>::iterator>);
    static_assert(std::random_access_iterator<std::vector<int>::iterator>);
    std::println("integral<int> = {}   integral<double> = {}", std::integral<int>, std::integral<double>);
    std::println("totally_ordered<Marker> = {}", std::totally_ordered<Marker>);
    std::println("same_as<int, int> = {}   convertible_to<int, double> = {}",
                 std::same_as<int, int>, std::convertible_to<int, double>);
    std::println("derived_from<std::string, std::string> = {}", std::derived_from<std::string, std::string>);

    // A few of the standard concepts, by family:
    //   numbers      std::integral  std::signed_integral  std::unsigned_integral  std::floating_point
    //   comparison   std::equality_comparable  std::totally_ordered
    //   objects      std::copyable  std::movable  std::default_initializable
    //   conversion   std::same_as<A, B>  std::convertible_to<From, To>  std::derived_from<D, B>
    //   callables    std::invocable<F, Args...>  std::predicate<F, Args...>
    //   iterators    std::forward_iterator  std::random_access_iterator ... (14.2)
    //   ranges       std::ranges::range  std::ranges::input_range  std::ranges::random_access_range ... (15.2)
    return 0;
}
