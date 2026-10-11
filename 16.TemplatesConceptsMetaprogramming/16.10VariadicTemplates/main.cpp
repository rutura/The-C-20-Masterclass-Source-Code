#include <concepts>
#include <cstddef>
#include <print>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// 1. A parameter PACK: a template parameter that stands for any number of
//    types (zero, one, many). `Args...` is the pack of types, `args...` the
//    pack of the values. sizeof...(args) is how many there are.
// ---------------------------------------------------------------------------
template <typename... Args>
void count_args(Args... args) {
    std::println("  {} arguments", sizeof...(args));
}

// ---------------------------------------------------------------------------
// 2. A FOLD EXPRESSION applies an operator across a whole pack.
//      (pack + ...)         pack1 + (pack2 + (pack3 + ...))     unary right fold
//      (init + ... + pack)  ((init + pack1) + pack2) + ...       binary left fold, with a start value
// ---------------------------------------------------------------------------
template <typename... Numbers>
auto sum_all(Numbers... numbers) {
    return (0 + ... + numbers);                      // the 0 also gives an answer for an empty pack
}

template <typename... Flags>
bool all_true(Flags... flags) {
    return (... && flags);                           // true for an empty pack
}

// The comma operator as the folded operator: do something for every element.
template <typename... Args>
void print_line(const Args&... args) {
    ((std::print("{} ", args)), ...);
    std::println();
}

// A constrained pack (16.7): every argument must be the same type as the first.
template <typename T, typename... Rest>
    requires (std::same_as<T, Rest> && ...)
T largest_of(T first, Rest... rest) {
    T best{first};
    ((best = rest > best ? rest : best), ...);
    return best;
}

// ---------------------------------------------------------------------------
// 3. Forwarding. A type that counts what happens to it:
// ---------------------------------------------------------------------------
struct Probe {
    static inline int copies{0};
    static inline int moves{0};

    Probe() = default;
    Probe(const Probe&) { ++copies; }
    Probe(Probe&&) noexcept { ++moves; }

    static void reset() { copies = 0; moves = 0; }
};

// In a function template, `T&&` with a T that is DEDUCED is not an rvalue
// reference (10.8). It is a FORWARDING REFERENCE: it binds to anything. If you
// pass an lvalue, T becomes `Probe&`; if you pass an rvalue, T becomes `Probe`.
//
// Inside, though, `value` has a name, so it is an lvalue, whatever was passed.
template <typename T>
void keep_wrong(T&& value) {
    [[maybe_unused]] Probe stored{value};            // always a copy
}

// std::forward<T>(value) gives the value back as it arrived: an rvalue if an
// rvalue was passed, an lvalue if an lvalue was passed.
template <typename T>
void keep_right(T&& value) {
    [[maybe_unused]] Probe stored{std::forward<T>(value)};
}

// The same idea for any number of arguments: pass them all on, unchanged.
// This is how std::make_unique (9.10) and vector::emplace_back (14.3) work.
struct Reading {
    std::string station;
    double celsius;
};

class Log {
public:
    template <typename... Args>
    void emplace(Args&&... args) {
        items_.emplace_back(std::forward<Args>(args)...);       // construct in place from the arguments
    }

    std::size_t size() const { return items_.size(); }
    const Reading& last() const { return items_.back(); }

private:
    std::vector<Reading> items_;
};

int main() {

    std::println("--- a parameter pack");
    count_args();
    count_args(1);
    count_args(1, 2.5, std::string{"north"});

    std::println("\n--- fold expressions");
    std::println("sum_all()              = {}", sum_all());
    std::println("sum_all(1, 2, 3)       = {}", sum_all(1, 2, 3));
    std::println("sum_all(1, 2.5, 3)     = {}", sum_all(1, 2.5, 3));
    std::println("all_true(true, 1 > 0)  = {}", all_true(true, 1 > 0));
    std::println("all_true(true, false)  = {}", all_true(true, false));
    std::print("print_line:            ");
    print_line(21, 24.5, std::string{"north"}, 'S');
    std::println("largest_of(3, 8, 5)   = {}", largest_of(3, 8, 5));
    // largest_of(3, 8.5);                     // error: constraint not satisfied, int is not double

    std::println("\n--- forwarding: lvalues and rvalues");
    Probe existing;
    Probe::reset();
    keep_wrong(Probe{});
    std::println("keep_wrong(rvalue):    {} copies, {} moves   (the temporary was copied)", Probe::copies, Probe::moves);

    Probe::reset();
    keep_right(Probe{});
    std::println("keep_right(rvalue):    {} copies, {} moves   (the temporary was moved)", Probe::copies, Probe::moves);

    Probe::reset();
    keep_right(existing);
    std::println("keep_right(lvalue):    {} copies, {} moves   (a named object must be copied)", Probe::copies, Probe::moves);

    std::println("\n--- passing any number of arguments on");
    Log log;
    log.emplace("north", 18.5);                      // goes straight to Reading{"north", 18.5}
    log.emplace(std::string{"south"}, 24.0);
    std::println("{} readings, last: {} {}", log.size(), log.last().station, log.last().celsius);
    return 0;
}
