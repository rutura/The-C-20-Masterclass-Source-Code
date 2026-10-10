#include <algorithm>
#include <compare>
#include <cstddef>
#include <format>
#include <print>
#include <string>
#include <utility>
#include <vector>

/*
    Chapter 12 assignment - solutions
*/

// Provided for exercise 2.
struct Wind {
    double speed;
    double heading;
};

// ---------------------------------------------------------------------
// Exercise 1 - arithmetic operators
//
// The compound operator is the real work and a member. The binary operators
// are hidden friends built from it, with the left operand taken by value, so
// that it is already the copy to modify and return.
// ---------------------------------------------------------------------
class Vec2 {
public:
    Vec2(double x, double y) : x_{x}, y_{y} {}

    double x() const { return x_; }
    double y() const { return y_; }

    Vec2& operator+=(const Vec2& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Vec2 operator-() const { return Vec2{-x_, -y_}; }

    friend Vec2 operator+(Vec2 a, const Vec2& b) {
        a += b;
        return a;
    }

    friend Vec2 operator*(Vec2 v, double factor) {
        return Vec2{v.x_ * factor, v.y_ * factor};
    }

    friend Vec2 operator*(double factor, Vec2 v) {
        return v * factor;
    }

private:
    double x_;
    double y_;
};

// ---------------------------------------------------------------------
// Exercise 2 - std::formatter
//
// parse() hands the part after the colon to the formatter of double, and
// format() lets that same formatter write each number, so {:.1f} works on both.
// ---------------------------------------------------------------------
template <>
struct std::formatter<Wind> {
    std::formatter<double> number;

    constexpr auto parse(std::format_parse_context& context) {
        return number.parse(context);
    }

    auto format(const Wind& wind, std::format_context& context) const {
        context.advance_to(number.format(wind.speed, context));
        context.advance_to(std::format_to(context.out(), " km/h at "));
        context.advance_to(number.format(wind.heading, context));
        return std::format_to(context.out(), " deg");
    }
};

// ---------------------------------------------------------------------
// Exercise 3 - comparison
//
// "= default" compares major, then minor, then patch: the right order for a
// version, and it also writes operator==.
// ---------------------------------------------------------------------
struct Version {
    int major;
    int minor;
    int patch;

    auto operator<=>(const Version&) const = default;
};

std::string to_text(const Version& version) {
    return std::format("{}.{}.{}", version.major, version.minor, version.patch);
}

// ---------------------------------------------------------------------
// Exercise 4 - the subscript operator
// ---------------------------------------------------------------------
class Grid {
public:
    Grid(std::size_t rows, std::size_t columns)
        : rows_{rows}, columns_{columns}, cells_(rows * columns, 0.0) {}

    std::size_t rows() const { return rows_; }
    std::size_t columns() const { return columns_; }

    double& operator[](std::size_t row, std::size_t column) {
        return cells_[row * columns_ + column];
    }

    const double& operator[](std::size_t row, std::size_t column) const {
        return cells_[row * columns_ + column];
    }

private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<double> cells_;
};

// ---------------------------------------------------------------------
// Exercise 5 - the call operator
// ---------------------------------------------------------------------
class Clamp {
public:
    Clamp(double low, double high) : low_{low}, high_{high} {}

    double operator()(double value) const {
        return std::clamp(value, low_, high_);
    }

private:
    double low_;
    double high_;
};

// ---------------------------------------------------------------------
// Exercise 6 - conversions
//
// Every conversion is explicit, so a Percent never turns into a number or a
// truth value by accident. An explicit operator bool is still used
// automatically in conditions (if, while, !, && and ||).
// ---------------------------------------------------------------------
class Percent {
public:
    explicit Percent(double value) : value_{value} {}

    explicit operator double() const { return value_; }
    explicit operator bool() const { return value_ > 0.0; }

private:
    double value_;
};

// ---------------------------------------------------------------------
// Exercise 7 - user-defined literals
// ---------------------------------------------------------------------
struct Mass {
    double kilograms;
};

Mass operator+(Mass a, Mass b) {
    return Mass{a.kilograms + b.kilograms};
}

constexpr Mass operator""_kg(long double value) {
    return Mass{static_cast<double>(value)};
}

constexpr Mass operator""_g(long double value) {
    return Mass{static_cast<double>(value) / 1000.0};
}

// ---------------------------------------------------------------------
// Exercise 8 - a pipe operator
//
// Each step is a function object that takes a Series and returns a new one.
// operator| calls the step with the series, and returns the result, which is
// what lets the next | take over.
// ---------------------------------------------------------------------
struct Series {
    std::vector<double> values;
};

struct Scale {
    double factor;

    Series operator()(Series series) const {
        for (double& value : series.values) {
            value *= factor;
        }
        return series;
    }
};

struct Offset {
    double amount;

    Series operator()(Series series) const {
        for (double& value : series.values) {
            value += amount;
        }
        return series;
    }
};

template <typename Step>
Series operator|(Series series, Step step) {
    return step(std::move(series));
}

int main() {

    std::println("--- Exercise 1: arithmetic operators ---");
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};
    Vec2 sum{a + b};
    std::println("a + b = ({}, {})", sum.x(), sum.y());
    Vec2 negated{-a};
    std::println("-a = ({}, {})", negated.x(), negated.y());
    Vec2 twice{2.0 * a};
    std::println("2 * a = ({}, {})", twice.x(), twice.y());
    Vec2 triple{a * 3.0};
    std::println("a * 3 = ({}, {})", triple.x(), triple.y());
    a += b;
    std::println("after a += b: ({}, {})", a.x(), a.y());

    std::println("\n--- Exercise 2: std::formatter ---");
    std::println("{}", Wind{12.5, 270.0});
    std::println("{:.1f}", Wind{12.5, 270.0});

    std::println("\n--- Exercise 3: comparison ---");
    std::vector<Version> versions{{1, 2, 0}, {1, 10, 0}, {0, 9, 2}, {1, 0, 0}};
    std::ranges::sort(versions);
    for (const Version& version : versions) {
        std::print("{} ", to_text(version));
    }
    std::println("");
    std::println("1.10.0 > 1.2.0: {}", Version{1, 10, 0} > Version{1, 2, 0});

    std::println("\n--- Exercise 4: the subscript operator ---");
    Grid grid{2, 3};
    grid[0, 0] = 1.0;
    grid[1, 2] = 5.0;
    double total{0.0};
    for (std::size_t row{0}; row < grid.rows(); ++row) {
        for (std::size_t column{0}; column < grid.columns(); ++column) {
            total += grid[row, column];
        }
    }
    std::println("grid[1, 2] = {}, total = {}", grid[1, 2], total);

    std::println("\n--- Exercise 5: the call operator ---");
    std::vector<double> raw{-5.0, 12.0, 40.0, 18.0, 100.0};
    std::vector<double> clamped(raw.size());
    std::ranges::transform(raw, clamped.begin(), Clamp{0.0, 30.0});
    for (double value : clamped) {
        std::print("{} ", value);
    }
    std::println("");

    std::println("\n--- Exercise 6: conversions ---");
    for (const Percent& percent : {Percent{75.0}, Percent{0.0}}) {
        std::println("{} percent, truthy: {}", static_cast<double>(percent), percent ? "yes" : "no");
    }

    std::println("\n--- Exercise 7: user-defined literals ---");
    Mass total_mass{2.5_kg + 500.0_g};
    std::println("{} kg", total_mass.kilograms);

    std::println("\n--- Exercise 8: a pipe operator ---");
    Series result{Series{{1.0, 2.0, 3.0}} | Scale{2.0} | Offset{1.0}};
    for (double value : result.values) {
        std::print("{} ", value);
    }
    std::println("");

    return 0;
}
