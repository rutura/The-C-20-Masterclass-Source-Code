#include <concepts>
#include <ostream>
#include <print>
#include <string>
#include <vector>

// 16.7 used the concepts of the standard library. You can write your own: a
// concept is a named, reusable requirement.

// ---------------------------------------------------------------------------
// 1. A concept built from things you already know: traits (16.6) and other
//    concepts, joined with && and ||.
// ---------------------------------------------------------------------------
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
concept SmallNumber = Number<T> && (sizeof(T) <= 4);

// ---------------------------------------------------------------------------
// 2. A concept built from a requires EXPRESSION: "these expressions must
//    compile". The parameters after `requires` are made-up names of the type,
//    used only to write the expressions. Nothing is ever executed.
// ---------------------------------------------------------------------------
template <typename T>
concept Addable = requires(T a, T b) {
    a + b;                                           // simple requirement: this expression must compile
};

// Needs an output stream (chapter 3's std::cout << value) to accept the value.
template <typename T>
concept Streamable = requires(std::ostream& stream, const T& value) {
    stream << value;
};

template <typename T>
concept Resettable = requires(T& item) {
    item.reset();                                    // a member function reset() must exist
};

// A compound requirement also checks what the expression gives back.
template <typename T>
concept Measurable = requires(const T& item) {
    { item.size() } -> std::convertible_to<std::size_t>;      // size() exists AND its result converts to size_t
};

// A type requirement: the type must have a nested type called value_type.
template <typename T>
concept HasValueType = requires {
    typename T::value_type;
};

// A concept for the weather station: something that can report a temperature.
template <typename T>
concept Sensor = requires(const T& sensor) {
    { sensor.celsius() } -> std::convertible_to<double>;
    { sensor.name() } -> std::convertible_to<std::string>;
};

// ---------------------------------------------------------------------------
// Types to test the concepts on.
// ---------------------------------------------------------------------------
struct Thermometer {
    double reading{21.5};
    double celsius() const { return reading; }
    std::string name() const { return "roof"; }
};

struct Counter {
    int count{3};
    void reset() { count = 0; }
};

struct Silent {};                                    // can do nothing

// Using a concept to constrain a template, as in 16.7.
void report(const Sensor auto& sensor) {
    std::println("{} reads {} C", sensor.name(), sensor.celsius());
}

// ---------------------------------------------------------------------------
// 3. SUBSUMPTION: when two constrained overloads both fit, the compiler picks
//    the MORE CONSTRAINED one, if one concept is built from the other.
// ---------------------------------------------------------------------------
void classify(Number auto value) {
    std::println("  {}: some number", value);
}

void classify(SmallNumber auto value) {              // SmallNumber includes Number, so this is more specific
    std::println("  {}: a number of at most 4 bytes", value);
}

int main() {

    std::println("--- concepts from other concepts");
    std::println("Number<int> = {}   Number<std::string> = {}", Number<int>, Number<std::string>);
    std::println("SmallNumber<int> = {}   SmallNumber<double> = {}   SmallNumber<float> = {}",
                 SmallNumber<int>, SmallNumber<double>, SmallNumber<float>);

    std::println("\n--- concepts from requires expressions");
    std::println("Addable<int> = {}   Addable<std::string> = {}   Addable<Silent> = {}",
                 Addable<int>, Addable<std::string>, Addable<Silent>);
    std::println("Streamable<int> = {}   Streamable<std::string> = {}   Streamable<Silent> = {}",
                 Streamable<int>, Streamable<std::string>, Streamable<Silent>);
    std::println("Resettable<Counter> = {}   Resettable<int> = {}", Resettable<Counter>, Resettable<int>);
    std::println("Measurable<std::string> = {}   Measurable<int> = {}", Measurable<std::string>, Measurable<int>);
    std::println("HasValueType<std::vector<int>> = {}   HasValueType<int> = {}",
                 HasValueType<std::vector<int>>, HasValueType<int>);
    std::println("Sensor<Thermometer> = {}   Sensor<Counter> = {}", Sensor<Thermometer>, Sensor<Counter>);

    std::println("\n--- using the Sensor concept");
    report(Thermometer{});
    // report(Counter{});                      // error: Counter does not satisfy Sensor

    std::println("\n--- the more constrained overload wins");
    classify(7);                                // int: both fit, the one with SmallNumber is more specific
    classify(2.5);                              // double is 8 bytes: only the general one fits
    classify(2.5f);                             // float is 4 bytes: the specific one

    // Why not just use the traits of 16.6 in a static_assert? A concept gives
    // the requirement a NAME, which can be reused, combined and chosen
    // between, and it fails at the CALL, so overloads can step aside.
    return 0;
}
