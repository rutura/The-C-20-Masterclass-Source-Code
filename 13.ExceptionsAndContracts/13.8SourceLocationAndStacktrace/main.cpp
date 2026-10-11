#include <print>
#include <source_location>
#include <stacktrace>
#include <stdexcept>
#include <string>

// std::source_location::current() as a DEFAULT ARGUMENT is evaluated at the
// call site, so the caller's file and line arrive without a macro.
void log_failure(const std::string& message,
                 std::source_location where = std::source_location::current()) {
    std::println("[{}:{}] {}: {}", where.file_name(), where.line(), where.function_name(), message);
}

class TracedError : public std::runtime_error {
public:
    explicit TracedError(const std::string& message,
                         std::source_location where = std::source_location::current())
        : std::runtime_error{message + " (at line " + std::to_string(where.line()) + ")"},
          trace_{std::stacktrace::current()} {}

    const std::stacktrace& trace() const noexcept { return trace_; }

private:
    std::stacktrace trace_;
};

double read_sensor(int id) {
    if (id < 0) {
        throw TracedError{"negative sensor id"};
    }
    return 20.0 + id;
}

double average(int first, int second) {
    return (read_sensor(first) + read_sensor(second)) / 2.0;
}

int main() {

    log_failure("the first problem");
    log_failure("the second problem");

    try {
        average(1, -1);
    }
    catch (const TracedError& error) {
        std::println("\ncaught: {}", error.what());
        std::println("the stack when it was created ({} frames):", error.trace().size());
        for (const auto& frame : error.trace()) {
            std::println("  {}", std::to_string(frame));
        }
    }
    return 0;
}
