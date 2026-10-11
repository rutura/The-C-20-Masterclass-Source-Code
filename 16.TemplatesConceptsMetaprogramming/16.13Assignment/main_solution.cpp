#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "matrix.h"

// ---- Exercise 1 ------------------------------------------------------------

template <typename T>
T clamped(T value, T low, T high) {
    return value < low ? low : (value > high ? high : value);
}

template <typename To, typename From>
To as(From value) {
    return static_cast<To>(value);
}

// ---- Exercise 2 ------------------------------------------------------------

void print_labelled(auto label, auto value) {
    std::println("{}: {}", label, value);
}

// ---- Exercise 3 ------------------------------------------------------------

template <typename T>
class Series {
public:
    Series(std::initializer_list<T> start) : items_{start} {}

    void add(const T& value) { items_.push_back(value); }
    std::size_t size() const { return items_.size(); }

    const T& largest() const {
        const T* best{&items_.front()};
        for (const T& item : items_) {
            if (*best < item) {
                best = &item;
            }
        }
        return *best;
    }

    double mean() const {
        double total{0.0};
        for (const T& item : items_) {
            total += item;
        }
        return total / static_cast<double>(items_.size());
    }

private:
    std::vector<T> items_;
};

// ---- Exercise 4 ------------------------------------------------------------

template <typename T, std::size_t N>
class FixedStack {
public:
    static_assert(N > 0, "a FixedStack needs room for at least one value");

    bool push(const T& value) {
        if (size_ == N) {
            return false;
        }
        items_[size_] = value;
        ++size_;
        return true;
    }

    std::optional<T> pop() {
        if (size_ == 0) {
            return std::nullopt;
        }
        --size_;
        return items_[size_];
    }

private:
    std::array<T, N> items_{};
    std::size_t size_{0};
};

// ---- Exercise 5 ------------------------------------------------------------

template <std::size_t N>
using Narrowest = std::conditional_t<(N <= 255), std::uint8_t,
                  std::conditional_t<(N <= 65535), std::uint16_t, std::uint32_t>>;

// ---- Exercise 6 ------------------------------------------------------------

template <typename T>
concept Measurement = requires(const T& item) {
    { item.value() } -> std::convertible_to<double>;
    { item.unit() } -> std::convertible_to<std::string_view>;
};

struct Temperature {
    double degrees;
    double value() const { return degrees; }
    std::string_view unit() const { return "C"; }
};

struct Humidity {
    int percent;
    int value() const { return percent; }
    std::string unit() const { return "%"; }
};

struct Broken {};

void report(const Measurement auto& measurement) {
    std::println("{} {}", measurement.value(), measurement.unit());
}

auto half(std::integral auto value) {
    return value / 2;
}

auto half(std::floating_point auto value) {
    return value * 0.5;
}

// ---- Exercise 7 ------------------------------------------------------------

template <typename... Numbers>
double average_of_all(Numbers... numbers) {
    return static_cast<double>((0 + ... + numbers)) / static_cast<double>(sizeof...(numbers));
}

template <typename... Args>
void print_all(const Args&... args) {
    ((std::print("{} ", args)), ...);
    std::println();
}

template <typename... Numbers>
bool all_positive(Numbers... numbers) {
    return (... && (numbers > 0));
}

// ---- Exercise 8 ------------------------------------------------------------

constexpr int sum_of_squares(int upto) {
    int total{0};
    for (int i{1}; i <= upto; ++i) {
        total += i * i;
    }
    return total;
}

int main() {

    std::println("--- Exercise 1: function templates ---");
    std::println("clamped(35, 0, 30)         = {}", clamped(35, 0, 30));
    std::println("clamped(-4.5, 0.0, 30.0)   = {}", clamped(-4.5, 0.0, 30.0));
    std::println("clamped<double>(35, 0, 30) = {}", clamped<double>(35, 0, 30));
    std::println("as<int>(21.9)              = {}", as<int>(21.9));
    std::println("as<double>(21)             = {}", as<double>(21));

    std::println("\n--- Exercise 2: generic lambdas ---");
    double low{10.0};
    double high{30.0};
    auto between{[low, high](auto value) { return value >= low && value <= high; }};
    std::vector<int> counts{5, 15, 25, 35};
    std::vector<double> temperatures{12.5, 18.0, 21.5, 40.0};
    std::println("counts between 10 and 30: {}", std::ranges::count_if(counts, between));
    std::println("temperatures between 10 and 30: {}", std::ranges::count_if(temperatures, between));
    print_labelled("station", std::string{"north"});
    print_labelled(7, 21.5);

    std::println("\n--- Exercise 3: a class template ---");
    Series readings{18.5, 24.0, 21.5};
    Series<int> alarms{4, 12, 7};
    alarms.add(3);
    std::println("readings: {} values, largest {}, mean {:.2f}", readings.size(), readings.largest(), readings.mean());
    std::println("alarms:   {} values, largest {}, mean {:.2f}", alarms.size(), alarms.largest(), alarms.mean());

    std::println("\n--- Exercise 4: a value as a template parameter ---");
    FixedStack<int, 3> stack;
    for (int value : {1, 2, 3, 4}) {
        std::println("push {}: {}", value, stack.push(value) ? "ok" : "full");
    }
    for (int i{0}; i < 4; ++i) {
        auto popped{stack.pop()};
        if (popped) {
            std::println("pop: {}", *popped);
        } else {
            std::println("pop: nothing");
        }
    }

    std::println("\n--- Exercise 5: type traits ---");
    std::println("Narrowest<200>   is {} byte(s)", sizeof(Narrowest<200>));
    std::println("Narrowest<3000>  is {} byte(s)", sizeof(Narrowest<3000>));
    std::println("Narrowest<70000> is {} byte(s)", sizeof(Narrowest<70000>));
    static_assert(std::is_same_v<Narrowest<10>, std::uint8_t>);
    std::println("is_integral<int> {}, is_integral<double> {}, is_arithmetic<std::string> {}",
                 std::is_integral_v<int>, std::is_integral_v<double>, std::is_arithmetic_v<std::string>);

    std::println("\n--- Exercise 6: concepts ---");
    report(Temperature{21.5});
    report(Humidity{64});
    static_assert(Measurement<Temperature> && Measurement<Humidity> && !Measurement<Broken>);
    std::println("half(21) = {}   half(21.0) = {}", half(21), half(21.0));

    std::println("\n--- Exercise 7: variadic templates ---");
    std::println("average_of_all(1, 2, 3, 4) = {}", average_of_all(1, 2, 3, 4));
    std::print("print_all: ");
    print_all("north", 21, 24.5);
    std::println("all_positive(3, 1.5, 7)  = {}", all_positive(3, 1.5, 7));
    std::println("all_positive(3, -1, 7)   = {}", all_positive(3, -1, 7));

    std::println("\n--- Exercise 8: at compile time ---");
    static_assert(sum_of_squares(4) == 30);
    constexpr Matrix<int, 2, 2> scale{2, 0, 0, 3};
    constexpr auto squared{scale * scale};
    static_assert(squared[0, 0] == 4 && squared[1, 1] == 9 && squared[0, 1] == 0);
    std::println("sum_of_squares(4) = {}", sum_of_squares(4));
    std::println("scale * scale:\n{}", squared);
    return 0;
}
