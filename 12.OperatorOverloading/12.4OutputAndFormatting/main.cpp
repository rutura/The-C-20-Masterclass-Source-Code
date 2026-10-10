#include <format>
#include <iostream>
#include <print>

class Vec2 {
public:
    Vec2(double x, double y) : x_{x}, y_{y} {}

    double x() const { return x_; }
    double y() const { return y_; }

    // THE CLASSIC WAY. Output with << takes a std::ostream on the left, which
    // is not our class, so it cannot be a member. It is a free function, and a
    // friend only if it needs the private data (here the getters would do).
    // It returns the stream so that  std::cout << a << b  chains.
    friend std::ostream& operator<<(std::ostream& out, const Vec2& v) {
        return out << '(' << v.x_ << ", " << v.y_ << ')';
    }

private:
    double x_;
    double y_;
};

// THE MODERN WAY: teach std::format (and so std::print and std::println) about
// the type by specializing std::formatter. This is boilerplate you can copy;
// what it means is chapter 16 (templates). Three parts:
//   - the std::formatter<Vec2> type, which says "this is how to format a Vec2"
//   - parse(): reads the part after the colon in "{:...}"
//   - format(): writes the value
template <>
struct std::formatter<Vec2> {
    // Reuse the formatter of double for the two numbers, so that a format spec
    // such as {:.1f} works on a Vec2 for free.
    std::formatter<double> number;

    constexpr auto parse(std::format_parse_context& context) {
        return number.parse(context);
    }

    auto format(const Vec2& v, std::format_context& context) const {
        context.advance_to(std::format_to(context.out(), "("));
        context.advance_to(number.format(v.x(), context));
        context.advance_to(std::format_to(context.out(), ", "));
        context.advance_to(number.format(v.y(), context));
        return std::format_to(context.out(), ")");
    }
};

int main() {

    Vec2 wind{3.14159, 4.0};

    // Without either of the two pieces above, this would not compile:
    //     std::println("{}", wind);                // error: no formatter for Vec2

    // Old code and old tutorials do this:
    std::cout << "with operator<<:  " << wind << '\n';

    // New code does this, and it is the one to prefer: type-checked format
    // strings, and a format spec that works.
    std::println("with std::formatter:  {}", wind);
    std::println("with a format spec:   {:.2f}", wind);
    std::println("with width:           {:8.1f}", wind);

    // A whole line, built with std::format and stored in a string.
    std::string line{std::format("wind is {:.1f}", wind)};
    std::println("{}", line);

    // Which to write? Write the formatter for new code. Write operator<< too
    // if the class must work with std::cout, with logging libraries or with
    // anything else built on streams. They are independent: one does not
    // provide the other.
    return 0;
}
