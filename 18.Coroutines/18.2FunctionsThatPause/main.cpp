#include <cstddef>
#include <format>
#include <generator>
#include <print>
#include <string>
#include <vector>

// A function runs from its first line to its last, and then its locals are
// gone. A COROUTINE is a function that can stop in the middle, hand a value to
// its caller, and later continue from the same line with its locals intact.
//
// The weather station sends a report as lines: a title, one line per reading,
// and a closing line. We hand the lines out ONE AT A TIME.

// ---- The old way: a class that remembers where it was --------------------
// Every "where was I?" has to be written by hand, as a state.
class ReportLines {
public:
    explicit ReportLines(const std::vector<double>& readings)
        : readings_{readings} {}

    bool has_next() const { return phase_ != Phase::Finished; }

    std::string next() {
        switch (phase_) {
        case Phase::Title:
            phase_ = readings_.empty() ? Phase::Closing : Phase::Readings;
            return "station report";
        case Phase::Readings: {
            std::string line{std::format("reading {}: {} C", index_ + 1, readings_[index_])};
            ++index_;
            if (index_ == readings_.size()) {
                phase_ = Phase::Closing;
            }
            return line;
        }
        case Phase::Closing:
        default:
            phase_ = Phase::Finished;
            return "end of report";
        }
    }

private:
    enum class Phase { Title, Readings, Closing, Finished };

    const std::vector<double>& readings_;
    Phase phase_{Phase::Title};
    std::size_t index_{0};
};

// ---- The new way: the same thing as a coroutine --------------------------
// `co_yield` hands a value to the caller and PAUSES right here. The compiler
// writes the class above for us: the phase is "which co_yield am I stopped
// at", and index_ is an ordinary local variable.
std::generator<std::string> report_lines(const std::vector<double>& readings) {
    co_yield "station report";
    std::size_t number{1};
    for (double celsius : readings) {
        co_yield std::format("reading {}: {} C", number, celsius);
        ++number;
    }
    co_yield "end of report";
}

// ---- Watching the pauses --------------------------------------------------
std::generator<int> countdown(int from) {
    for (int value{from}; value > 0; --value) {
        std::println("  [countdown] giving {}", value);
        co_yield value;
        std::println("  [countdown] resumed after {}", value);
    }
    std::println("  [countdown] reached the end");
}

int main() {
    std::vector<double> readings{18.5, 24.0, 21.5};

    std::println("--- by hand: a state machine");
    ReportLines by_hand{readings};
    while (by_hand.has_next()) {
        std::println("{}", by_hand.next());
    }

    std::println("\n--- the same report as a coroutine");
    for (const std::string& line : report_lines(readings)) {
        std::println("{}", line);
    }

    // Calling a coroutine does NOT run its body. It builds the generator and
    // stops before the first line. Each step of the loop resumes it until the
    // next co_yield. Read the output as a conversation between the two.
    std::println("\n--- who runs when");
    std::generator<int> numbers{countdown(2)};
    std::println("main: the generator exists, nothing has run");
    for (int value : numbers) {
        std::println("main: received {}", value);
    }
    std::println("main: the loop is over");

    // The keywords that make a function a coroutine (any one of them is enough):
    //
    //     co_yield value;     give a value to the caller and pause
    //     co_return value;    finish, optionally with a final value (18.7)
    //     co_await thing;     pause until `thing` is ready (18.6)
    //
    // The return type decides what the coroutine IS. std::generator<T> is a
    // sequence of T. In 18.4 and 18.5 we write such a type ourselves.
    return 0;
}
