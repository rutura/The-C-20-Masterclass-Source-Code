#include <expected>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>

// One job, four ways of reporting failure: turn text such as "21.5" into a
// temperature. The text may not be a number at all.

// 1. A RETURN CODE plus an output parameter: the C way. Nothing forces the
//    caller to look at the code, and the output is meaningless on failure.
bool parse_with_code(std::string_view text, double& result) {
    try {
        std::size_t used{0};
        result = std::stod(std::string{text}, &used);
        return used == text.size();
    }
    catch (...) {
        return false;
    }
}

// 2. std::optional: "a value, or nothing". The failure carries no reason.
std::optional<double> parse_optional(std::string_view text) {
    double value{0.0};
    if (parse_with_code(text, value)) {
        return value;
    }
    return std::nullopt;
}

// 3. std::expected (C++23): "a value, or an error that says why".
std::expected<double, std::string> parse_expected(std::string_view text) {
    double value{0.0};
    if (parse_with_code(text, value)) {
        return value;
    }
    return std::unexpected{std::string{"not a number: '"} + std::string{text} + "'"};
}

// 4. An EXCEPTION: the failure leaves the function by a different road, and
//    cannot be ignored: if nobody catches it, the program ends.
double parse_throwing(std::string_view text) {
    double value{0.0};
    if (!parse_with_code(text, value)) {
        throw std::invalid_argument{"not a number: '" + std::string{text} + "'"};
    }
    return value;
}

int main() {

    for (std::string_view text : {"21.5", "warm"}) {
        std::println("--- parsing '{}'", text);

        double a{0.0};
        std::println("  return code: {}", parse_with_code(text, a) ? "ok" : "failed");

        auto b{parse_optional(text)};
        std::println("  optional:    {}", b ? std::to_string(*b) : "nothing");

        auto c{parse_expected(text)};
        std::println("  expected:    {}", c ? std::to_string(*c) : c.error());

        try {
            std::println("  exception:   {}", parse_throwing(text));
        }
        catch (const std::invalid_argument& error) {
            std::println("  exception:   caught: {}", error.what());
        }
    }

    // Which to choose:
    //   failure is NORMAL and expected (user input, a missing file)   optional or expected
    //   failure is RARE or cannot be handled where it happens         exception
    //   constructors and operators (no return value to use)           exception
    return 0;
}
