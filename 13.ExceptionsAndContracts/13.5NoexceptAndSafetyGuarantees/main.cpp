#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Part 1: noexcept, and why vector cares.
// ---------------------------------------------------------------------------

// Counts what the vector does with it while growing. The two types differ in
// exactly one word: noexcept on the move constructor.
int copies{0};
int moves{0};

struct Careful {
    Careful() = default;
    Careful(const Careful&) { ++copies; }
    Careful(Careful&&) noexcept { ++moves; }
};

struct Nervous {
    Nervous() = default;
    Nervous(const Nervous&) { ++copies; }
    Nervous(Nervous&&) { ++moves; }              // may throw, as far as the compiler knows
};

template <typename T>
void grow_to(int count) {
    copies = 0;
    moves = 0;
    std::vector<T> items;
    for (int i{0}; i < count; ++i) {
        items.emplace_back();
    }
    std::println("  {} elements: {} copies, {} moves", count, copies, moves);
}

// ---------------------------------------------------------------------------
// Part 2: the exception safety guarantees, on one small class.
// ---------------------------------------------------------------------------

class ReadingLog {
public:
    // Basic guarantee: if parsing fails halfway, nothing leaks and the log is
    // still valid, but it keeps whatever was added before the failure.
    void append_basic(const std::vector<std::string>& texts) {
        for (const auto& text : texts) {
            values_.push_back(std::stod(text));        // may throw invalid_argument
        }
    }

    // Strong guarantee: either everything is added, or the log is exactly as
    // it was. Do the risky work on a copy, then commit with operations that
    // cannot fail (a move, a swap).
    void append_strong(const std::vector<std::string>& texts) {
        std::vector<double> staged{values_};
        for (const auto& text : texts) {
            staged.push_back(std::stod(text));
        }
        values_ = std::move(staged);
    }

    std::size_t size() const noexcept { return values_.size(); }

private:
    std::vector<double> values_;
};

int main() {

    std::println("growing a vector of a type with a noexcept move:");
    grow_to<Careful>(100);
    std::println("growing a vector of a type whose move may throw:");
    grow_to<Nervous>(100);

    // noexcept is also an operator that asks the compiler a question.
    std::println("\nstd::string move is noexcept: {}", noexcept(std::string{std::declval<std::string>()}));

    std::println("\nbasic guarantee:");
    ReadingLog basic;
    try {
        basic.append_basic({"20.5", "21.0", "oops", "22.0"});
    }
    catch (const std::invalid_argument&) {
        std::println("  failed, log holds {} readings (valid, but half done)", basic.size());
    }

    std::println("strong guarantee:");
    ReadingLog strong;
    try {
        strong.append_strong({"20.5", "21.0", "oops", "22.0"});
    }
    catch (const std::invalid_argument&) {
        std::println("  failed, log holds {} readings (as if nothing happened)", strong.size());
    }

    // A noexcept function that throws does not propagate: the program ends.
    // Uncomment to see std::terminate.
    //     []() noexcept { throw std::runtime_error{"too late"}; }();
    return 0;
}
