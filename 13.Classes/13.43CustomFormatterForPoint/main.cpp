// std::print/std::format only know how to format the types the standard
// library ships a formatter for - strings, numbers, chrono types, and so
// on. A user-defined type like the Point class from a few lectures ago
// (14.42) needs its own std::formatter specialization before {} can print
// it directly - there's no automatic fallback to a stream-insertion
// operator the way <iostream> would have offered.

#include <print>
#include <format>

class Point {
public:
    Point(double x, double y) : m_x{x}, m_y{y} {}

    double x() const { return m_x; }
    double y() const { return m_y; }

private:
    double m_x{};
    double m_y{};
};

// A formatter specialization has two parts: parse() reads whatever's
// between the ':' and the closing '}' in the format spec (e.g. the ".2"
// in "{:.2}"), and format() produces the actual output using it.
template <>
struct std::formatter<Point> {
    // Inheriting from std::formatter<double> reuses its parsing logic -
    // any precision/width spec valid for a double (like ".2") is
    // automatically valid here too, with no parsing code of our own to write.
    std::formatter<double> m_doubleFormatter;

    constexpr auto parse(std::format_parse_context& ctx) {
        return m_doubleFormatter.parse(ctx);
    }

    auto format(const Point& point, std::format_context& ctx) const {
        auto out = ctx.out();
        out = std::format_to(out, "(");
        out = m_doubleFormatter.format(point.x(), ctx);
        out = std::format_to(out, ", ");
        ctx.advance_to(out);
        out = m_doubleFormatter.format(point.y(), ctx);
        out = std::format_to(out, ")");
        return out;
    }
};

int main() {

    Point origin{0.0, 0.0};
    Point p1{3.5, 4.25};

    // Default formatting - no spec, just {}.
    std::println("origin: {}", origin);
    std::println("p1: {}", p1);

    // The precision spec after the ':' is handled entirely by
    // m_doubleFormatter - Point's own format() never has to parse ".2f"
    // itself, it just reuses what std::formatter<double> already knows.
    // (The 'f' matters: without it, .N means N *significant digits*, the
    // same std::formatter<double> rule that applies to a plain double -
    // not specific to Point.)
    std::println("p1 with 2 decimal places: {:.2f}", p1);
    std::println("p1 with 4 decimal places: {:.4f}", p1);

    // Works in a println's positional arguments too, same as any other
    // formattable type.
    std::println("distance check: {} vs {}", origin, p1);

    return 0;
}
