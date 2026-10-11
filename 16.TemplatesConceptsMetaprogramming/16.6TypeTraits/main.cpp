#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <type_traits>
#include <vector>

// <type_traits> is a library of QUESTIONS and TRANSFORMATIONS about types, all
// answered while the program is being compiled. You have already seen a few:
// std::is_nothrow_move_constructible_v (13.5) and std::is_trivially_copyable_v
// (13.9) were used in a static_assert. Now we meet the family.

struct Reading {
    double celsius;
};

struct Careful {
    Careful(Careful&&) noexcept {}
    Careful(const Careful&) = default;
};

struct Nervous {
    Nervous(Nervous&&) {}                     // may throw, as far as the compiler knows
    Nervous(const Nervous&) = default;
};

// A trait inside a template: a clear message at compile time, written by us.
template <typename T>
T half_of(T value) {
    static_assert(std::is_arithmetic_v<T>, "half_of needs a number");
    return value / 2;
}

// A trait that CHOOSES a type. The smallest unsigned integer that can hold the
// numbers 0 to N: a byte for up to 255, two bytes up to 65535, otherwise four.
template <std::size_t N>
using SmallestIndex = std::conditional_t<(N <= 255), std::uint8_t,
                      std::conditional_t<(N <= 65535), std::uint16_t, std::uint32_t>>;

int main() {

    // The _v at the end of a trait's name means "give me the VALUE": a bool
    // constant known at compile time.
    std::println("--- questions about a type (each answer is a bool, known at compile time)");
    std::println("is_integral_v<int>               = {}", std::is_integral_v<int>);
    std::println("is_integral_v<double>            = {}", std::is_integral_v<double>);
    std::println("is_floating_point_v<double>      = {}", std::is_floating_point_v<double>);
    std::println("is_arithmetic_v<char>            = {}", std::is_arithmetic_v<char>);           // integers and floating point
    std::println("is_arithmetic_v<std::string>     = {}", std::is_arithmetic_v<std::string>);
    std::println("is_pointer_v<int*>               = {}", std::is_pointer_v<int*>);
    std::println("is_const_v<const int>            = {}", std::is_const_v<const int>);
    std::println("is_same_v<int, int>              = {}", std::is_same_v<int, int>);
    std::println("is_same_v<int, long>             = {}", std::is_same_v<int, long>);
    std::println("is_convertible_v<int, double>    = {}", std::is_convertible_v<int, double>);
    std::println("is_convertible_v<std::string, int> = {}", std::is_convertible_v<std::string, int>);

    // The same family explains the promise made in 13.5: a vector moves its
    // elements on growth only if the move cannot throw.
    std::println("\n--- the questions of earlier chapters");
    std::println("is_nothrow_move_constructible_v<Careful> = {}", std::is_nothrow_move_constructible_v<Careful>);
    std::println("is_nothrow_move_constructible_v<Nervous> = {}", std::is_nothrow_move_constructible_v<Nervous>);
    std::println("is_trivially_copyable_v<Reading>         = {}", std::is_trivially_copyable_v<Reading>);
    std::println("is_trivially_copyable_v<std::string>     = {}", std::is_trivially_copyable_v<std::string>);

    // Transformations produce a TYPE. The result is named with _t.
    std::println("\n--- transformations (the answer is a type, so we ask is_same_v about it)");
    std::println("remove_const_t<const int> is int           : {}", std::is_same_v<std::remove_const_t<const int>, int>);
    std::println("remove_reference_t<int&> is int            : {}", std::is_same_v<std::remove_reference_t<int&>, int>);
    std::println("remove_cvref_t<const int&> is int          : {}", std::is_same_v<std::remove_cvref_t<const int&>, int>);
    std::println("add_const_t<int> is const int              : {}", std::is_same_v<std::add_const_t<int>, const int>);
    std::println("common_type_t<int, double> is double       : {}", std::is_same_v<std::common_type_t<int, double>, double>);
    std::println("make_unsigned_t<int> is unsigned int       : {}", std::is_same_v<std::make_unsigned_t<int>, unsigned int>);

    // decltype(expression) is the type that an expression has. It is how a
    // trait can be asked about a VALUE you have, rather than a type you name.
    std::println("\n--- decltype");
    auto total{2 + 3.5};
    std::println("type of 2 + 3.5 is double                   : {}", std::is_same_v<decltype(total), double>);
    std::vector<int> counts{1, 2, 3};
    std::println("type of counts.size() is std::size_t        : {}", std::is_same_v<decltype(counts.size()), std::size_t>);
    std::println("type of counts[0] is a reference to an int  : {}", std::is_same_v<decltype(counts[0]), int&>);

    // Using a trait to choose a type.
    std::println("\n--- conditional_t chooses a type at compile time");
    std::println("sizeof(SmallestIndex<100>)     = {} byte", sizeof(SmallestIndex<100>));
    std::println("sizeof(SmallestIndex<1000>)    = {} bytes", sizeof(SmallestIndex<1000>));
    std::println("sizeof(SmallestIndex<100000>)  = {} bytes", sizeof(SmallestIndex<100000>));

    // Using a trait to reject a wrong type with a clear message.
    std::println("\n--- static_assert with a trait");
    std::println("half_of(21) = {}   half_of(24.0) = {}", half_of(21), half_of(24.0));
    // half_of(std::string{"north"});    // error: half_of needs a number

    // Traits can be used in constant expressions: with static_assert, or to
    // define constants.
    static_assert(std::is_same_v<SmallestIndex<10>, std::uint8_t>);
    constexpr bool cheap_to_copy{std::is_trivially_copyable_v<Reading> && sizeof(Reading) <= 16};
    std::println("\nReading is cheap to copy: {}", cheap_to_copy);
    return 0;
}
