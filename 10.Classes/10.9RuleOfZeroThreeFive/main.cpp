#include <algorithm>
#include <cstddef>
#include <memory>
#include <print>
#include <type_traits>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Version 1: the log owns a raw block. Because it writes a destructor, it must
// write the other four special member functions as well: the RULE OF FIVE.
// (This is the whole of 10.6 to 10.8, in one place.)
// ---------------------------------------------------------------------------
class RawLog {
public:
    explicit RawLog(std::size_t capacity)
        : data_{new double[capacity]{}}, capacity_{capacity} {}

    ~RawLog() { delete[] data_; }                                    // 1. destructor

    RawLog(const RawLog& other)                                      // 2. copy constructor
        : data_{new double[other.capacity_]}, capacity_{other.capacity_}, size_{other.size_} {
        std::copy_n(other.data_, other.size_, data_);
    }

    RawLog& operator=(const RawLog& other) {                         // 3. copy assignment
        if (this != &other) {
            double* fresh{new double[other.capacity_]};
            std::copy_n(other.data_, other.size_, fresh);
            delete[] data_;
            data_ = fresh;
            capacity_ = other.capacity_;
            size_ = other.size_;
        }
        return *this;
    }

    RawLog(RawLog&& other) noexcept                                  // 4. move constructor
        : data_{std::exchange(other.data_, nullptr)},
          capacity_{std::exchange(other.capacity_, 0)},
          size_{std::exchange(other.size_, 0)} {}

    RawLog& operator=(RawLog&& other) noexcept {                     // 5. move assignment
        if (this != &other) {
            delete[] data_;
            data_ = std::exchange(other.data_, nullptr);
            capacity_ = std::exchange(other.capacity_, 0);
            size_ = std::exchange(other.size_, 0);
        }
        return *this;
    }

    void add(double reading) { if (size_ < capacity_) { data_[size_++] = reading; } }
    std::size_t size() const { return size_; }

private:
    double* data_;
    std::size_t capacity_;
    std::size_t size_{0};
};

// ---------------------------------------------------------------------------
// Version 2: the log holds a std::vector. The vector already knows how to
// destroy, copy and move itself, so the class needs NONE of the five. This is
// the RULE OF ZERO: let the members do the work, and write no special member
// functions at all.
// ---------------------------------------------------------------------------
class VectorLog {
public:
    explicit VectorLog(std::size_t capacity) { readings_.reserve(capacity); }

    void add(double reading) { readings_.push_back(reading); }
    std::size_t size() const { return readings_.size(); }

private:
    std::vector<double> readings_;
};

// ---------------------------------------------------------------------------
// Version 3: the log holds a unique_ptr to its block. A unique_ptr cannot be
// copied, so neither can this class, and that is exactly right for something
// with one owner. The compiler-written move works. Still the rule of zero.
// ---------------------------------------------------------------------------
class UniqueLog {
public:
    explicit UniqueLog(std::size_t capacity)
        : data_{std::make_unique<double[]>(capacity)}, capacity_{capacity} {}

    void add(double reading) { if (size_ < capacity_) { data_[size_++] = reading; } }
    std::size_t size() const { return size_; }

private:
    std::unique_ptr<double[]> data_;
    std::size_t capacity_;
    std::size_t size_{0};
};

// ---------------------------------------------------------------------------
// =delete and =default: saying it out loud. A class for something that must
// exist only once says so, and the compiler enforces it.
// ---------------------------------------------------------------------------
class SerialPort {
public:
    explicit SerialPort(int number) : number_{number} {}

    SerialPort(const SerialPort&) = delete;                // two objects cannot share one port
    SerialPort& operator=(const SerialPort&) = delete;

    SerialPort(SerialPort&&) = default;                    // but a port can be handed over
    SerialPort& operator=(SerialPort&&) = default;
    ~SerialPort() = default;

    int number() const { return number_; }

private:
    int number_;
};

template <typename T>
void show(const char* name) {
    std::println("  {:<10} copyable: {:<5}  movable: {:<5}  move can throw: {}",
                 name,
                 std::is_copy_constructible_v<T>,
                 std::is_move_constructible_v<T>,
                 !std::is_nothrow_move_constructible_v<T>);
}

int main() {

    // The same questions, asked of all four classes at compile time.
    std::println("what each class can do:");
    show<RawLog>("RawLog");
    show<VectorLog>("VectorLog");
    show<UniqueLog>("UniqueLog");
    show<SerialPort>("SerialPort");

    std::println("\nthey behave the same where they should:");

    RawLog raw{4};
    raw.add(60.0);
    RawLog raw_copy{raw};
    std::println("  RawLog copy has {} reading(s), original still {}", raw_copy.size(), raw.size());

    VectorLog vector_log{4};
    vector_log.add(60.0);
    VectorLog vector_copy{vector_log};
    std::println("  VectorLog copy has {} reading(s), original still {}", vector_copy.size(), vector_log.size());

    UniqueLog unique_log{4};
    unique_log.add(60.0);
    // UniqueLog unique_copy{unique_log};      // error: copying a unique_ptr member is deleted
    UniqueLog unique_moved{std::move(unique_log)};
    std::println("  UniqueLog moved has {} reading(s)", unique_moved.size());

    SerialPort port{3};
    // SerialPort second{port};                // error: the copy constructor is deleted
    SerialPort handed_over{std::move(port)};
    std::println("  SerialPort {} was handed over", handed_over.number());

    // Which version would you rather maintain? RawLog is thirty lines of
    // careful code, and every line is a chance for a bug. VectorLog is eight
    // lines and has none.
    return 0;
}
