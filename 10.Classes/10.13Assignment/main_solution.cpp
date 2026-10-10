#include <algorithm>
#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

/*
    Chapter 10 assignment - solutions
*/

// ---------------------------------------------------------------------
// Exercise 1 - a class that protects its data
//
// The only way to change celsius_ is set_celsius(), which refuses a value
// that cannot exist. The rule is in one place, and cannot be bypassed.
// ---------------------------------------------------------------------
class Thermometer {
public:
    bool set_celsius(double celsius) {
        if (celsius < -273.15) {
            return false;
        }
        celsius_ = celsius;
        return true;
    }

    double celsius() const { return celsius_; }
    double fahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }

private:
    double celsius_{0.0};
};

// ---------------------------------------------------------------------
// Exercise 2 - constructors
//
// The two short constructors delegate, so the real setup is written once.
// A const member (id_) can only be given its value in the initializer list.
// ---------------------------------------------------------------------
class Alarm {
public:
    Alarm(int id, const std::string& name, double threshold)
        : id_{id}, name_{name}, threshold_{threshold} {}

    Alarm(int id, const std::string& name)
        : Alarm{id, name, 30.0} {}

    Alarm()
        : Alarm{0, "unnamed"} {}

    std::string describe() const {
        return std::format("Alarm #{} '{}' triggers above {:.1f}", id_, name_, threshold_);
    }

private:
    const int id_;
    std::string name_;
    double threshold_{30.0};
};

// ---------------------------------------------------------------------
// Exercise 3 - const member functions and mutable
//
// get() is const, so a const Lookup& can call it. It still updates reads_,
// which is bookkeeping and not part of the object's real state, so reads_ is
// mutable.
// ---------------------------------------------------------------------
class Lookup {
public:
    void add(int value) { values_.push_back(value); }

    int get(std::size_t index) const {
        ++reads_;
        return values_[index];
    }

    std::size_t reads() const { return reads_; }

private:
    std::vector<int> values_;
    mutable std::size_t reads_{0};
};

void print_all(const Lookup& lookup, std::size_t count) {
    for (std::size_t i{0}; i < count; ++i) {
        std::print("{} ", lookup.get(i));
    }
    std::println("");
}

// ---------------------------------------------------------------------
// Exercise 4 - RAII
//
// The destructor runs on every way out of the scope, including the early
// return in work(), and in reverse order of construction.
// ---------------------------------------------------------------------
class ScopeLabel {
public:
    explicit ScopeLabel(const std::string& name)
        : name_{name} {
        std::println("enter {}", name_);
    }

    ~ScopeLabel() {
        std::println("leave {}", name_);
    }

private:
    std::string name_;
};

void work(bool bail_out) {
    ScopeLabel label{"work"};
    if (bail_out) {
        return;
    }
    std::println("working");
}

// ---------------------------------------------------------------------
// Exercise 5 - the rule of five
//
// It owns a raw block, so it must write all five. The copy operations make a
// new block. The move operations steal the old one and leave the source empty
// (and valid: deleting nullptr is allowed).
// ---------------------------------------------------------------------
class Buffer {
public:
    explicit Buffer(std::size_t size)
        : data_{new int[size]{}}, size_{size} {}

    ~Buffer() {
        delete[] data_;
    }

    Buffer(const Buffer& other)
        : data_{new int[other.size_]}, size_{other.size_} {
        std::copy_n(other.data_, other.size_, data_);
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            int* fresh{new int[other.size_]};       // allocate first, so a failure changes nothing
            std::copy_n(other.data_, other.size_, fresh);
            delete[] data_;
            data_ = fresh;
            size_ = other.size_;
        }
        return *this;
    }

    Buffer(Buffer&& other) noexcept
        : data_{std::exchange(other.data_, nullptr)},
          size_{std::exchange(other.size_, 0)} {}

    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            size_ = std::exchange(other.size_, 0);
        }
        return *this;
    }

    int get(std::size_t index) const { return data_[index]; }
    void set(std::size_t index, int value) { data_[index] = value; }
    std::size_t size() const { return size_; }

private:
    int* data_;
    std::size_t size_;
};

// ---------------------------------------------------------------------
// Exercise 6 - the rule of zero
//
// The vector already knows how to destroy, copy and move itself, so the class
// writes none of the five and is still copyable and nothrow-movable.
// ---------------------------------------------------------------------
class SafeBuffer {
public:
    explicit SafeBuffer(std::size_t size)
        : data_(size) {}                            // parentheses: a vector of `size` zeros (7.4)

    int get(std::size_t index) const { return data_[index]; }
    void set(std::size_t index, int value) { data_[index] = value; }
    std::size_t size() const { return data_.size(); }

private:
    std::vector<int> data_;
};

// ---------------------------------------------------------------------
// Exercise 7 - static and this
//
// issued_ is shared by every Ticket. Copying is deleted: a copy would carry
// the same number_ as the original, so two tickets would claim to be one.
// ---------------------------------------------------------------------
class Ticket {
public:
    explicit Ticket(const std::string& note)
        : number_{++issued_}, note_{note} {}

    Ticket(const Ticket&) = delete;
    Ticket& operator=(const Ticket&) = delete;

    Ticket& with_note(const std::string& note) {
        note_ = note;
        return *this;                               // lets calls be chained
    }

    static int issued() { return issued_; }

    std::string describe() const {
        return std::format("ticket {}: '{}'", number_, note_);
    }

private:
    static inline int issued_{0};
    int number_;
    std::string note_;
};

// ---------------------------------------------------------------------
// Exercise 8 - composition and aggregates
//
// Range has no rules, so it is an aggregate. Gauge HAS a Range and a name,
// and keeps the rule "what counts as low, normal or high".
// ---------------------------------------------------------------------
struct Range {
    double low;
    double high;
};

enum class Level { low, normal, high };

std::string level_name(Level level) {
    switch (level) {
        case Level::low:    return "low";
        case Level::normal: return "normal";
        case Level::high:   return "high";
    }
    return "unknown";
}

class Gauge {
public:
    Gauge(const std::string& name, Range range)
        : name_{name}, range_{range} {}

    Level classify(double value) const {
        if (value < range_.low) {
            return Level::low;
        }
        if (value > range_.high) {
            return Level::high;
        }
        return Level::normal;
    }

    Range range() const { return range_; }

private:
    std::string name_;
    Range range_;
};

int main() {

    std::println("--- Exercise 1: Thermometer ---");
    Thermometer thermometer;
    thermometer.set_celsius(21.5);
    std::println("{} C = {:.1f} F", thermometer.celsius(), thermometer.fahrenheit());
    const bool accepted{thermometer.set_celsius(-300.0)};
    std::println("set_celsius(-300): {}, still {} C", accepted ? "accepted" : "rejected", thermometer.celsius());

    std::println("\n--- Exercise 2: Alarm ---");
    Alarm hot{7, "hot", 35.0};
    Alarm default_level{8, "default-level"};
    Alarm unnamed;
    std::println("{}", hot.describe());
    std::println("{}", default_level.describe());
    std::println("{}", unnamed.describe());

    std::println("\n--- Exercise 3: Lookup ---");
    Lookup lookup;
    lookup.add(10);
    lookup.add(20);
    lookup.add(30);
    print_all(lookup, 3);
    std::println("reads: {}", lookup.reads());

    std::println("\n--- Exercise 4: ScopeLabel ---");
    {
        ScopeLabel outer{"outer"};
        {
            ScopeLabel inner{"inner"};
        }
    }
    work(true);

    std::println("\n--- Exercise 5: Buffer ---");
    Buffer a{3};
    a.set(0, 7);
    Buffer b{a};
    b.set(0, 99);
    std::println("copy: b[0] = {}, original a[0] = {}", b.get(0), a.get(0));
    Buffer c{std::move(a)};
    std::println("moved c: size {}, c[0] = {}, a (moved-from) size {}", c.size(), c.get(0), a.size());

    std::println("\n--- Exercise 6: SafeBuffer ---");
    std::println("SafeBuffer copyable: {}, nothrow movable: {}",
                 std::is_copy_constructible_v<SafeBuffer>,
                 std::is_nothrow_move_constructible_v<SafeBuffer>);

    std::println("\n--- Exercise 7: Ticket ---");
    Ticket first{"storm warning"};
    Ticket second{"hail"};
    second.with_note("frost");
    std::println("{}", first.describe());
    std::println("{}", second.describe());
    std::println("issued so far: {}", Ticket::issued());

    std::println("\n--- Exercise 8: Gauge ---");
    Gauge gauge{"outdoor", Range{.low = 15.0, .high = 30.0}};
    auto [low, high]{gauge.range()};
    std::println("range {} to {}", low, high);
    for (double value : {10.0, 22.0, 35.0}) {
        std::println("{} -> {}", value, level_name(gauge.classify(value)));
    }

    return 0;
}
