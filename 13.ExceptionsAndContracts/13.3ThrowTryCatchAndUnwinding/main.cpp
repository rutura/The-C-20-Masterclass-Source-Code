#include <print>
#include <stdexcept>
#include <string>

// A helper that announces when it is destroyed, to make the unwinding visible.
class Trace {
public:
    explicit Trace(std::string name) : name_{std::move(name)} {
        std::println("    {} created", name_);
    }

    ~Trace() {
        std::println("    {} destroyed", name_);
    }

private:
    std::string name_;
};

double read_sensor(int id) {
    Trace trace{"read_sensor trace"};
    if (id < 0) {
        // throw: stop here, leave the function, and look for a handler.
        throw std::out_of_range{"sensor id " + std::to_string(id) + " does not exist"};
    }
    return 20.0 + id;
}

double average_of_two(int first, int second) {
    Trace trace{"average_of_two trace"};
    double a{read_sensor(first)};
    double b{read_sensor(second)};          // an exception here skips everything below
    std::println("    (average_of_two finished normally)");
    return (a + b) / 2.0;
}

int main() {

    std::println("a call that works:");
    std::println("  result {}\n", average_of_two(1, 3));

    std::println("a call that throws:");
    try {
        std::println("  result {}", average_of_two(1, -7));
    }
    // catch: a handler for one kind of exception. It receives the exception by
    // const reference (never by value: that would slice it, 11.4).
    catch (const std::out_of_range& error) {
        std::println("  caught: {}", error.what());
    }
    std::println("  the program carries on\n");

    // Handlers are tried in order, and the first match wins. A handler for a
    // base class catches derived exceptions too, so put the specific ones first.
    std::println("handlers in order:");
    try {
        read_sensor(-1);
    }
    catch (const std::invalid_argument&) {
        std::println("  not this one");
    }
    catch (const std::logic_error& error) {              // out_of_range derives from logic_error
        std::println("  logic_error handler caught: {}", error.what());
    }

    // catch (...) catches anything at all, with no way to look at it. Use it
    // as a last resort, for example to log and then rethrow.
    try {
        throw 42;                                         // anything can be thrown, even an int
    }
    catch (...) {
        std::println("\n  catch (...) caught something unknown");
    }

    // An exception that nobody catches calls std::terminate and ends the program.
    // Uncomment to see it:
    //     read_sensor(-1);
    return 0;
}
