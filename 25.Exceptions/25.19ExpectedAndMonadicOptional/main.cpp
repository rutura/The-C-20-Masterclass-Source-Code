// This chapter has been about exceptions: throwing, catching, and
// propagating a failure up the call stack. But not every failure needs to
// unwind the stack - parsing user input that might be malformed, looking
// something up that might not exist. std::expected (C++23) represents
// "either a value, or a reason it failed" as an ordinary return value, no
// throw/catch required - useful specifically for failures the immediate
// caller is expected to handle right there, not propagate.

#include <print>
#include <format>
#include <expected>
#include <optional>
#include <string>

// std::expected<T, E> holds either a T (success) or an E (the error) -
// never both, never neither. Compare this signature to a function that
// would instead throw on bad input: the possibility of failure is visible
// right here, in the return type, without reading the function body.
std::expected<int, std::string> parseAge(const std::string& text) {
    if (text.empty()) {
        return std::unexpected("input was empty");
    }

    try {
        int age = std::stoi(text);
        if (age < 0 || age > 150) {
            return std::unexpected(std::format("{} is not a plausible age", age));
        }
        return age;
    } catch (const std::exception&) {
        // std::stoi throws on genuinely malformed input - caught here and
        // converted into this function's own error type, so the exception
        // never has to leave parseAge at all.
        return std::unexpected(std::format("'{}' is not a number", text));
    }
}

void reportAge(const std::string& input) {
    std::expected<int, std::string> result = parseAge(input);

    if (result.has_value()) {
        std::println("'{}' parsed as age {}", input, result.value());
    } else {
        std::println("'{}' failed: {}", input, result.error());
    }
}

// std::optional<int> half(int x) from earlier chapters only ever said
// "here's a value, or nothing" - no way to say *why* there was nothing.
// Chaining several such steps together used to mean checking has_value()
// after every single one.
std::optional<int> half(int x) {
    if (x % 2 != 0) return std::nullopt;
    return x / 2;
}

int main() {

    reportAge("34");
    reportAge("");
    reportAge("abc");
    reportAge("200");

    std::println("");

    // and_then chains a step that itself returns an optional, short-
    // circuiting to nullopt the moment any step in the chain fails -
    // instead of nesting three separate if(has_value()) checks.
    auto chained = half(80).and_then(half).and_then(half);
    std::println("half(half(half(80))) = {}", chained.value_or(-1));

    auto chainedOdd = half(7).and_then(half);
    std::println("half(7).and_then(half) has a value: {}", chainedOdd.has_value());

    // transform applies a plain function (one that doesn't itself return
    // an optional) to the value inside, only if there is one.
    auto doubled = half(10).transform([](int x) { return x * 2; });
    std::println("half(10).transform(x*2) = {}", doubled.value_or(-1));

    // or_else supplies a fallback optional to use if the chain failed,
    // instead of just falling back to a plain default value the way
    // value_or does.
    auto withFallback = half(7).or_else([] { return std::optional<int>{0}; });
    std::println("half(7).or_else(0) = {}", withFallback.value_or(-1));

    return 0;
}
