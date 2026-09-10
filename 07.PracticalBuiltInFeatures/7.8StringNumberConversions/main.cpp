#include <array>
#include <charconv>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

// Text in, numbers out - and back again. The old std::stoi / std::to_string
// pair is convenient; <charconv> is the modern, fast, no-surprises option.

int main() {
    // --- number -> text ---

    // std::to_string is the quick way. It uses the "C" locale, so a
    // double always prints with '.' and a fixed default precision.
    std::string a{std::to_string(42)};
    std::string b{std::to_string(3.14159)};
    std::println("to_string(42)      : \"{}\"", a);
    std::println("to_string(3.14159) : \"{}\"", b);

    // --- text -> number, the convenient way ---

    // std::stoi / std::stod parse the leading number and stop. They
    // THROW on bad input: std::invalid_argument (no number) or
    // std::out_of_range (number too big for the type).
    try {
        int n{std::stoi("  128 apples")};              // leading spaces OK
        double d{std::stod("2.5e3")};
        std::println("stoi(\"  128 apples\") : {}", n);
        std::println("stod(\"2.5e3\")        : {}", d);

        int bad{std::stoi("hello")};                    // throws
        std::println("unreachable: {}", bad);
    } catch (const std::invalid_argument& ex) {
        std::println("stoi(\"hello\") threw invalid_argument: {}", ex.what());
    } catch (const std::out_of_range& ex) {
        std::println("out_of_range: {}", ex.what());
    }

    // --- text -> number, the modern way: std::from_chars ---

    // No exceptions, no locale, no allocation. It reports success through
    // an error code and tells you where parsing stopped. This is what you
    // reach for when parsing lots of fields (see the chapter project).
    std::string_view field{"3500"};
    int value{0};
    auto [ptr, ec]{std::from_chars(field.data(), field.data() + field.size(), value)};

    if (ec == std::errc{}) {
        std::println("from_chars parsed {} (stopped at offset {})",
                     value, ptr - field.data());
    } else if (ec == std::errc::invalid_argument) {
        std::println("from_chars: not a number");
    } else if (ec == std::errc::result_out_of_range) {
        std::println("from_chars: out of range");
    }

    // A field that is not a number: value is left untouched, ec is set.
    std::string_view junk{"n/a"};
    int parsed{-1};
    auto result{std::from_chars(junk.data(), junk.data() + junk.size(), parsed)};
    std::println("parsing \"n/a\": ok? {}, value still {}",
                 result.ec == std::errc{}, parsed);

    // --- number -> text, the modern way: std::to_chars ---

    // Writes into a caller-provided buffer, returns one-past-the-last
    // character written. No allocation.
    std::array<char, 32> buffer{};
    auto [end, ec2]{std::to_chars(buffer.data(), buffer.data() + buffer.size(), 987654)};
    if (ec2 == std::errc{}) {
        std::string_view written{buffer.data(), end};
        std::println("to_chars wrote \"{}\"", written);
    }

    return 0;
}
