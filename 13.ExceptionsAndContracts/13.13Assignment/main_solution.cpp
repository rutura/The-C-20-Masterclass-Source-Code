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

// Provided for exercise 8: a tiny test harness.
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

// ---- Exercise 1 ------------------------------------------------------------

double parse_percent(const std::string& text) {
    double value{0.0};
    auto result{std::from_chars(text.data(), text.data() + text.size(), value)};
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size()) {
        throw std::invalid_argument{"not a number: " + text};
    }
    if (value < 0.0 || value > 100.0) {
        throw std::out_of_range{"percent out of range: " + text};
    }
    return value;
}

// ---- Exercise 2 ------------------------------------------------------------

class CalibrationError : public std::runtime_error {
public:
    CalibrationError(int sensor_id, double offset)
        : std::runtime_error{std::format("sensor {} cannot be offset by {}", sensor_id, offset)},
          sensor_id_{sensor_id},
          offset_{offset} {}

    int sensor_id() const noexcept { return sensor_id_; }
    double offset() const noexcept { return offset_; }

private:
    int sensor_id_;
    double offset_;
};

void calibrate(int sensor_id, double offset) {
    if (std::abs(offset) > 5.0) {
        throw CalibrationError{sensor_id, offset};
    }
    std::println("sensor {} calibrated by {}", sensor_id, offset);
}

// ---- Exercise 3 ------------------------------------------------------------

std::expected<double, std::string> fahrenheit(int id) {
    return find_sensor(id).transform([](const Sensor& sensor) {
        return sensor.celsius * 9.0 / 5.0 + 32.0;
    });
}

// ---- Exercise 4 ------------------------------------------------------------

class ReadingBuffer {
public:
    // Strong guarantee: parse into a staging vector first, commit last.
    void add_all(const std::vector<std::string>& texts) {
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

// ---- Exercise 5 ------------------------------------------------------------

class Connection {
public:
    Connection() { ++open_count_; }
    ~Connection() { --open_count_; }

    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    static int open_count() { return open_count_; }

private:
    static inline int open_count_{0};
};

void send(int call, bool fail) {
    Connection connection;
    std::println("call {}: inside send, open = {}", call, Connection::open_count());
    if (fail) {
        throw std::runtime_error{"transmission failed"};
    }
}

// ---- Exercise 6 ------------------------------------------------------------

void load_station(const std::string& name) {
    try {
        read_sensor_file(name + ".dat");
    }
    catch (...) {
        std::throw_with_nested(std::runtime_error{"cannot load station " + name});
    }
}

void print_chain(const std::exception& error, int depth = 0) {
    std::println("{}{}", std::string(static_cast<std::size_t>(depth) * 2, ' '), error.what());
    try {
        std::rethrow_if_nested(error);
    }
    catch (const std::exception& cause) {
        print_chain(cause, depth + 1);
    }
}

// ---- Exercise 7 ------------------------------------------------------------

int copies{0};
int moves{0};

class Frame {
public:
    Frame() = default;
    Frame(const Frame&) { ++copies; }
    Frame(Frame&&) noexcept { ++moves; }
};

static_assert(std::is_nothrow_move_constructible_v<Frame>);

// ---- Exercise 8 ------------------------------------------------------------

double percent_of(double part, double whole) {
    if (whole == 0.0) {
        throw std::domain_error{"whole must not be zero"};
    }
    if (part < 0.0) {
        throw std::invalid_argument{"part must not be negative"};
    }
    return part / whole * 100.0;
}

int main() {

    std::println("--- Exercise 1: standard exceptions ---");
    for (const std::string text : {"42.5", "abc", "150", "12x"}) {
        try {
            std::println("{} -> {}", text, parse_percent(text));
        }
        catch (const std::invalid_argument& error) {
            std::println("{} -> invalid_argument: {}", text, error.what());
        }
        catch (const std::out_of_range& error) {
            std::println("{} -> out_of_range: {}", text, error.what());
        }
    }

    std::println("\n--- Exercise 2: a custom exception ---");
    calibrate(3, 1.5);
    try {
        calibrate(7, 9.0);
    }
    catch (const CalibrationError& error) {
        std::println("{}", error.what());
        std::println("caught by id: {}, offset {}", error.sensor_id(), error.offset());
    }

    std::println("\n--- Exercise 3: std::expected ---");
    for (int id : {1, 2, 9}) {
        auto result{fahrenheit(id)};
        if (result) {
            std::println("sensor {}: {:.1f} F", id, *result);
        } else {
            std::println("sensor {}: {}", id, result.error());
        }
    }

    std::println("\n--- Exercise 4: the strong guarantee ---");
    ReadingBuffer buffer;
    buffer.add_all({"1.5", "2.5", "3.5"});
    std::println("added 3 readings, size {}", buffer.size());
    try {
        buffer.add_all({"4.5", "oops", "6.5"});
    }
    catch (const std::invalid_argument&) {
        std::println("bad batch rejected, size still {}", buffer.size());
    }

    std::println("\n--- Exercise 5: unwinding and RAII ---");
    for (int call : {1, 2, 3}) {
        try {
            send(call, call != 2);
            std::println("call {} succeeded, open after = {}", call, Connection::open_count());
        }
        catch (const std::runtime_error&) {
            std::println("call {} failed, open after = {}", call, Connection::open_count());
        }
    }

    std::println("\n--- Exercise 6: nested exceptions ---");
    try {
        load_station("north");
    }
    catch (const std::exception& error) {
        print_chain(error);
    }

    std::println("\n--- Exercise 7: noexcept and vector ---");
    {
        std::vector<Frame> frames;
        for (int i{0}; i < 10; ++i) {
            frames.emplace_back();
        }
        std::println("copies: {}", copies);
        std::println("moves happened: {}", moves > 0);
    }

    std::println("\n--- Exercise 8: test it ---");
    check(percent_of(25.0, 100.0) == 25.0, "25 of 100 is 25 percent");
    check(percent_of(1.0, 4.0) == 25.0, "1 of 4 is 25 percent");
    check_throws<std::domain_error>([] { percent_of(1.0, 0.0); }, "zero whole is a domain_error");
    check_throws<std::invalid_argument>([] { percent_of(-1.0, 5.0); }, "negative part is invalid");
    check_throws<std::logic_error>([] { percent_of(1.0, 0.0); }, "domain_error is a logic_error");
    std::println("{} checks, {} failures", checks, failures);
    return failures == 0 ? 0 : 1;
}
