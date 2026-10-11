#include <expected>
#include <print>
#include <string>
#include <string_view>

// A sensor setting arrives as text such as "interval=30". Three things can go
// wrong, and the caller wants to know WHICH, not just that something did.
enum class ConfigError {
    MissingEquals,
    NotANumber,
    OutOfRange,
};

std::string_view describe(ConfigError error) {
    switch (error) {
        case ConfigError::MissingEquals: return "no '=' in the setting";
        case ConfigError::NotANumber:    return "the value is not a number";
        case ConfigError::OutOfRange:    return "the value is outside 1..3600";
    }
    return "unknown";
}

struct Setting {
    std::string name;
    std::string value;
};

// Each step either produces its result or an error, and never throws.
std::expected<Setting, ConfigError> split(std::string_view line) {
    auto equals{line.find('=')};
    if (equals == std::string_view::npos) {
        return std::unexpected{ConfigError::MissingEquals};
    }
    return Setting{std::string{line.substr(0, equals)}, std::string{line.substr(equals + 1)}};
}

std::expected<int, ConfigError> to_number(const Setting& setting) {
    try {
        std::size_t used{0};
        int number{std::stoi(setting.value, &used)};
        if (used != setting.value.size()) {
            return std::unexpected{ConfigError::NotANumber};
        }
        return number;
    }
    catch (...) {
        return std::unexpected{ConfigError::NotANumber};
    }
}

std::expected<int, ConfigError> check_range(int seconds) {
    if (seconds < 1 || seconds > 3600) {
        return std::unexpected{ConfigError::OutOfRange};
    }
    return seconds;
}

// The long way: test after every step. Correct, and noisy.
std::expected<int, ConfigError> interval_plain(std::string_view line) {
    auto setting{split(line)};
    if (!setting) {
        return std::unexpected{setting.error()};
    }
    auto number{to_number(*setting)};
    if (!number) {
        return std::unexpected{number.error()};
    }
    return check_range(*number);
}

// The chained way: and_then runs the next step only if the previous one
// succeeded; the first error skips everything after it and comes out unchanged.
std::expected<int, ConfigError> interval_chained(std::string_view line) {
    return split(line)
        .and_then(to_number)
        .and_then(check_range);
}

void show(std::string_view line) {
    auto result{interval_chained(line)};
    if (result) {
        std::println("  '{}' -> interval {} s", line, *result);
    } else {
        std::println("  '{}' -> error: {}", line, describe(result.error()));
    }
}

int main() {

    std::println("chained steps:");
    for (std::string_view line : {"interval=30", "interval", "interval=soon", "interval=99999"}) {
        show(line);
    }

    std::println("\nsame answer both ways: {}", interval_plain("interval=30") == interval_chained("interval=30"));

    // Other members of the family:
    auto good{interval_chained("interval=30")};
    auto bad{interval_chained("interval=zero")};

    std::println("\nvalue_or: {} and {}", good.value_or(60), bad.value_or(60));

    // transform changes the value and leaves an error alone.
    auto minutes{good.transform([](int seconds) { return seconds / 60.0; })};
    std::println("transform: {} minutes", *minutes);

    // transform_error changes the error type, here to a message for people.
    auto readable{bad.transform_error([](ConfigError e) { return std::string{describe(e)}; })};
    std::println("transform_error: {}", readable.error());

    // or_else gives a chance to recover from an error.
    auto recovered{bad.or_else([](ConfigError) -> std::expected<int, ConfigError> { return 60; })};
    std::println("or_else: {}", *recovered);

    // value() on an error is the bridge back to exceptions: it throws
    // std::bad_expected_access<ConfigError>.
    try {
        std::println("{}", bad.value());
    }
    catch (const std::bad_expected_access<ConfigError>& access) {
        std::println("value() on an error threw, error was: {}", describe(access.error()));
    }
    return 0;
}
