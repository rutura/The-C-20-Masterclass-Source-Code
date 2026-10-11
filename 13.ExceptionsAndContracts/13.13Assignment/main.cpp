#include <charconv>
#include <cmath>
#include <cstddef>
#include <exception>
#include <expected>
#include <format>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

/*
    Chapter 13 assignment - Exceptions and a first look at contracts

    Eight small jobs for the weather station, one idea of the chapter each.
    Write the functions and classes ABOVE main(), and the lines that use them
    in main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Catch exceptions by const reference, most specific handler first.
      - Mark with noexcept what cannot throw, and nothing else.
*/

// Provided for exercise 3.
struct Sensor {
    int id;
    double celsius;
};

std::expected<Sensor, std::string> find_sensor(int id) {
    switch (id) {
        case 1:  return Sensor{1, 21.5};
        case 2:  return Sensor{2, -3.0};
        default: return std::unexpected{"no sensor " + std::to_string(id)};
    }
}

// Provided for exercise 6.
void read_sensor_file(const std::string& name) {
    throw std::runtime_error{"cannot open " + name};
}

// Provided for exercise 8: a tiny test harness, the idea of 13.10 in short.
int checks{0};
int failures{0};

void check(bool ok, std::string_view what) {
    ++checks;
    if (!ok) {
        ++failures;
        std::println("  FAILED: {}", what);
    }
}

template <typename Expected, typename Code>
void check_throws(Code code, std::string_view what) {
    ++checks;
    try {
        code();
    }
    catch (const Expected&) {
        return;
    }
    catch (...) {
    }
    ++failures;
    std::println("  FAILED: {}", what);
}

// Write your functions and classes here, above main().


int main() {

    /*
        Exercise 1 - standard exceptions

        Write double parse_percent(const std::string& text). Use
        std::from_chars (<charconv>) to read a double from the whole text:

            double value{0.0};
            auto result{std::from_chars(text.data(), text.data() + text.size(), value)};
            // result.ec != std::errc{} means "no number", and
            // result.ptr != text.data() + text.size() means "extra characters"

        - not a number (or extra characters): throw std::invalid_argument
          with the message "not a number: <text>"
        - a number outside 0..100: throw std::out_of_range with the message
          "percent out of range: <text>"

        In main(), loop over "42.5", "abc", "150", "12x". Catch the two
        types in two separate handlers and print which one fired.

        Sample output:
            42.5 -> 42.5
            abc -> invalid_argument: not a number: abc
            150 -> out_of_range: percent out of range: 150
            12x -> invalid_argument: not a number: 12x
    */
    std::println("--- Exercise 1: standard exceptions ---");
    // TODO


    /*
        Exercise 2 - a custom exception

        Write class CalibrationError, derived from std::runtime_error (13.4),
        with a constructor CalibrationError(int sensor_id, double offset), a
        message of the form "sensor <id> cannot be offset by <offset>" (build
        it with std::format), and noexcept getters sensor_id() and offset().

        Write void calibrate(int sensor_id, double offset): it throws a
        CalibrationError when the offset is larger than 5 in either direction,
        otherwise it prints "sensor <id> calibrated by <offset>".

        In main(), calibrate sensor 3 by 1.5, then sensor 7 by 9.0 inside a
        try block. Catch CalibrationError and print the message and the data.

        Sample output:
            sensor 3 calibrated by 1.5
            sensor 7 cannot be offset by 9
            caught by id: 7, offset 9
    */
    std::println("\n--- Exercise 2: a custom exception ---");
    // TODO


    /*
        Exercise 3 - std::expected

        find_sensor() above returns a Sensor, or an error text. Write
        std::expected<double, std::string> fahrenheit(int id) WITHOUT an if:
        chain .transform(...) on the result of find_sensor so that the Celsius
        value becomes Fahrenheit (c * 9 / 5 + 32), and an error passes
        through untouched (13.7).

        In main(), print the result for sensors 1, 2 and 9, with one decimal.

        Sample output:
            sensor 1: 70.7 F
            sensor 2: 26.6 F
            sensor 9: no sensor 9
    */
    std::println("\n--- Exercise 3: std::expected ---");
    // TODO


    /*
        Exercise 4 - the strong guarantee

        Write class ReadingBuffer with a std::vector<double> and:
            void add_all(const std::vector<std::string>& texts)
            std::size_t size() const noexcept

        add_all converts every text with std::stod (which throws
        std::invalid_argument on bad text). It must give the STRONG guarantee
        (13.5): if any text is bad, the buffer is exactly as it was before the
        call. Hint: work on a copy and commit at the end.

        In main(), add {"1.5", "2.5", "3.5"}, print the size, then try to add
        {"4.5", "oops", "6.5"} and print the size again after catching.

        Sample output:
            added 3 readings, size 3
            bad batch rejected, size still 3
    */
    std::println("\n--- Exercise 4: the strong guarantee ---");
    // TODO


    /*
        Exercise 5 - unwinding and RAII

        Write class Connection. Its constructor counts one more open
        connection, its destructor one less, through a static member and a
        static function open_count(). It cannot be copied (= delete).

        Write void send(int call, bool fail): create a Connection, print
        "call <n>: inside send, open = <count>", and if fail is true throw
        std::runtime_error{"transmission failed"}.

        In main(), run calls 1, 2 and 3 where only call 2 succeeds (each in
        its own try block, catching std::runtime_error). After each call print
        how many connections are open. No call may leave one open.

        Sample output:
            call 1: inside send, open = 1
            call 1 failed, open after = 0
            call 2: inside send, open = 1
            call 2 succeeded, open after = 0
            call 3: inside send, open = 1
            call 3 failed, open after = 0
    */
    std::println("\n--- Exercise 5: unwinding and RAII ---");
    // TODO


    /*
        Exercise 6 - nested exceptions

        read_sensor_file() above always fails. Write void load_station(const
        std::string& name): call read_sensor_file(name + ".dat"), and when it
        throws, wrap the problem with std::throw_with_nested(...) in a new
        std::runtime_error{"cannot load station " + name} (13.6).

        Write void print_chain(const std::exception& error, int depth = 0):
        print the message indented by two spaces per level, then use
        std::rethrow_if_nested to print the cause one level deeper.

        In main(), call load_station("north") and print the chain.

        Sample output:
            cannot load station north
              cannot open north.dat
    */
    std::println("\n--- Exercise 6: nested exceptions ---");
    // TODO


    /*
        Exercise 7 - noexcept and the vector

        Two global counters, int copies and int moves, are yours to write.
        Write class Frame with a default constructor, a copy constructor that
        does ++copies, and a move constructor that does ++moves. Mark the move
        constructor noexcept, and prove it at compile time with:

            static_assert(std::is_nothrow_move_constructible_v<Frame>);

        In main(), emplace_back ten Frames into a std::vector<Frame> and print
        the counters. Then remove the noexcept, rebuild and look at the copies:
        why did the number change? (The exact number of moves depends on the
        standard library, so the output prints only whether any happened.)

        Sample output:
            copies: 0
            moves happened: true
    */
    std::println("\n--- Exercise 7: noexcept and vector ---");
    // TODO


    /*
        Exercise 8 - test it

        Write double percent_of(double part, double whole):
            - whole == 0   -> throw std::domain_error
            - part < 0     -> throw std::invalid_argument
            - otherwise    -> part / whole * 100

        Then write five checks with the provided harness: two with check()
        for normal results, and three with check_throws<...>() for the
        domain_error, the invalid_argument, and one that proves a
        domain_error is also caught as its base class std::logic_error.
        End main with the exit code from the harness.

        Sample output:
            5 checks, 0 failures
    */
    std::println("\n--- Exercise 8: test it ---");
    // TODO

    return failures == 0 ? 0 : 1;
}
