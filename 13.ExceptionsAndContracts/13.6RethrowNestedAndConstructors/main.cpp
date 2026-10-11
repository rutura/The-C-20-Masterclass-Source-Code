#include <exception>
#include <print>
#include <stdexcept>
#include <string>

class Part {
public:
    explicit Part(std::string name, bool fail = false) : name_{std::move(name)} {
        if (fail) {
            throw std::runtime_error{name_ + " could not be built"};
        }
        std::println("    {} built", name_);
    }

    ~Part() {
        std::println("    {} destroyed", name_);
    }

private:
    std::string name_;
};

// A constructor that fails: the object never finishes existing, so its
// destructor does not run. The members that WERE built are destroyed, in
// reverse order, which is why members that own things (RAII) make this safe.
class Station {
public:
    Station() : antenna_{"antenna"}, battery_{"battery", true}, display_{"display"} {
        std::println("    Station constructed");              // never reached
    }

    ~Station() {
        std::println("    Station destroyed");                // never runs either
    }

private:
    Part antenna_;
    Part battery_;
    Part display_;
};

// A function-try-block is the only way to see an exception thrown by the
// member initialisers. It can log or translate, but it cannot swallow:
// the exception is rethrown when the handler ends.
class Gateway {
public:
    Gateway() try : link_{"link", true} {
    }
    catch (const std::exception& error) {
        std::println("    Gateway constructor saw: {}", error.what());
    }

private:
    Part link_;
};

// ---------------------------------------------------------------------------
// Rethrow and nesting: add context without losing the original cause.
// ---------------------------------------------------------------------------

void read_file() {
    throw std::runtime_error{"file not found"};
}

void load_config() {
    try {
        read_file();
    }
    catch (const std::exception&) {
        // Wraps the active exception inside a new one. The cause travels along.
        std::throw_with_nested(std::runtime_error{"configuration could not be loaded"});
    }
}

void print_chain(const std::exception& error, int depth = 0) {
    std::println("  {}{}", std::string(static_cast<std::size_t>(depth) * 2, ' '), error.what());
    try {
        std::rethrow_if_nested(error);
    }
    catch (const std::exception& cause) {
        print_chain(cause, depth + 1);
    }
}

void log_and_pass_on() {
    try {
        read_file();
    }
    catch (...) {
        std::println("  logging the failure, then passing it on");
        throw;                                  // rethrows the SAME exception, not a copy
    }
}

int main() {

    std::println("a constructor that fails:");
    try {
        Station station;
    }
    catch (const std::exception& error) {
        std::println("  caught: {}\n", error.what());
    }

    std::println("function-try-block on a constructor:");
    try {
        Gateway gateway;
    }
    catch (const std::exception& error) {
        std::println("  main still receives it: {}\n", error.what());
    }

    std::println("nested exceptions:");
    try {
        load_config();
    }
    catch (const std::exception& error) {
        print_chain(error);
    }

    std::println("\nrethrow with throw;");
    try {
        log_and_pass_on();
    }
    catch (const std::exception& error) {
        std::println("  main caught: {}", error.what());
    }

    // Destructors are noexcept by default. Throwing out of one while another
    // exception is already unwinding ends the program, so never let one escape.
    return 0;
}
