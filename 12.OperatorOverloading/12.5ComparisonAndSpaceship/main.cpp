#include <algorithm>
#include <compare>
#include <format>
#include <print>
#include <string>
#include <utility>
#include <vector>

// A software version: 2.10.1 is newer than 2.9.9, because the numbers are
// compared one by one, not as text.
struct Version {
    int major;
    int minor;
    int patch;

    // C++20: the three-way comparison operator, the "spaceship" <=>. It
    // answers "less, equal or greater" in one go. Writing "= default" makes
    // the compiler compare the members in the order they are DECLARED, major
    // first, then minor, then patch: exactly what a version needs. The
    // compiler also writes operator== for you, and from these two it derives
    // all six comparisons: == != < <= > >=
    auto operator<=>(const Version&) const = default;
};

std::string to_text(const Version& v) {
    return std::format("{}.{}.{}", v.major, v.minor, v.patch);
}

// A class where the default is NOT what you want: two readings are ordered by
// their value only, and the label (which sensor) must not matter.
class Reading {
public:
    Reading(std::string sensor, double value) : sensor_{std::move(sensor)}, value_{value} {}

    double value() const { return value_; }
    const std::string& sensor() const { return sensor_; }

    // Compare by value alone. Comparing doubles with <=> gives a
    // std::partial_ordering, because a double can be NaN, which is neither less
    // than, equal to nor greater than anything.
    std::partial_ordering operator<=>(const Reading& other) const {
        return value_ <=> other.value_;
    }

    // operator== is NOT generated from a hand-written <=>, so it is written
    // too, and it must agree with the ordering.
    bool operator==(const Reading& other) const {
        return value_ == other.value_;
    }

private:
    std::string sensor_;
    double value_;
};

int main() {

    Version older{2, 9, 9};
    Version newer{2, 10, 1};

    // All six work, from one defaulted line.
    std::println("{} < {}   {}", to_text(older), to_text(newer), older < newer);
    std::println("{} == {}  {}", to_text(older), to_text(newer), older == newer);
    std::println("{} >= {}  {}", to_text(older), to_text(newer), older >= newer);

    // Because the type is now comparable with <, the standard algorithms can
    // sort it (chapter 15): no comparison function needed.
    std::vector<Version> versions{{1, 4, 0}, {2, 10, 1}, {2, 9, 9}, {1, 4, 3}};
    std::ranges::sort(versions);

    std::print("\nsorted: ");
    for (const Version& v : versions) {
        std::print("{} ", to_text(v));
    }
    std::println("");

    // The result of <=> can be used directly. It is a small object that says
    // which way the comparison went; std::is_lt, is_eq and is_gt read it.
    std::strong_ordering ordering{older <=> newer};
    std::println("\nolder <=> newer says less: {}, equal: {}", std::is_lt(ordering), std::is_eq(ordering));

    // The hand-written version: order by value, ignore the sensor.
    Reading north{"north", 21.5};
    Reading east{"east", 21.5};
    Reading roof{"roof", 30.0};

    std::println("\nnorth == east (different sensors, same value): {}", north == east);
    std::println("north < roof:  {}", north < roof);
    std::println("roof > east:   {}", roof > east);

    // Which comparison operators do you write?
    //   a plain bundle of data, members in the right order:   <=> = default
    //   something with its own idea of order or equality:     write <=> and ==
    //   equality only (no sensible order):                    write == alone
    return 0;
}
