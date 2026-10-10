#include <algorithm>
#include <cstddef>
#include <print>
#include <type_traits>
#include <utility>
#include <vector>

class ReadingLog {
public:
    explicit ReadingLog(std::size_t capacity)
        : data_{new double[capacity]{}}, capacity_{capacity} {}

    ReadingLog(const ReadingLog& other)
        : data_{new double[other.capacity_]}, capacity_{other.capacity_}, size_{other.size_} {
        std::copy_n(other.data_, other.size_, data_);
        std::println("  [copy] {} elements duplicated", size_);
    }

    ReadingLog& operator=(const ReadingLog& other) {
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

    // The MOVE constructor: it does not copy the block, it STEALS it. The new
    // log takes the pointer, and the old one is left holding nothing. No
    // allocation, no copying: the cost is a few assignments, however big the
    // log is. The parameter is ReadingLog&&, an "rvalue reference": it binds
    // to objects that are about to go away anyway.
    //
    // noexcept promises that it cannot throw. That promise matters: see the
    // vector demonstration below.
    ReadingLog(ReadingLog&& other) noexcept
        : data_{std::exchange(other.data_, nullptr)},
          capacity_{std::exchange(other.capacity_, 0)},
          size_{std::exchange(other.size_, 0)} {
        std::println("  [move] block stolen");
    }

    ReadingLog& operator=(ReadingLog&& other) noexcept {
        if (this != &other) {
            delete[] data_;                              // give up what we had
            data_ = std::exchange(other.data_, nullptr);
            capacity_ = std::exchange(other.capacity_, 0);
            size_ = std::exchange(other.size_, 0);
            std::println("  [move assign] block stolen");
        }
        return *this;
    }

    ~ReadingLog() {
        delete[] data_;                  // deleting nullptr is allowed and does nothing
    }

    bool add(double reading) {
        if (size_ == capacity_) {
            return false;
        }
        data_[size_++] = reading;
        return true;
    }

    std::size_t size() const { return size_; }

private:
    double* data_;
    std::size_t capacity_;
    std::size_t size_{0};
};

// A factory that returns a log by value. A returned temporary is built
// directly in the caller's variable (guaranteed since C++17): no copy and no
// move at all.
ReadingLog make_log(std::size_t capacity) {
    return ReadingLog{capacity};
}

// Two tiny types that count what happens to them, to see how std::vector
// treats a type depending on whether its move is noexcept.
int quiet_copies{0};
int quiet_moves{0};
int careless_copies{0};
int careless_moves{0};

struct Quiet {
    Quiet() = default;
    Quiet(const Quiet&) { ++quiet_copies; }
    Quiet(Quiet&&) noexcept { ++quiet_moves; }
};

struct Careless {
    Careless() = default;
    Careless(const Careless&) { ++careless_copies; }
    Careless(Careless&&) { ++careless_moves; }           // no noexcept
};

int main() {

    std::println("a copy, then a move:");
    ReadingLog original{1000};
    original.add(68.0);
    original.add(71.0);

    ReadingLog copy{original};
    ReadingLog moved{std::move(original)};
    std::println("  copy has {} readings, moved has {}", copy.size(), moved.size());

    // std::move does not move anything by itself. It is only a cast that says
    // "treat this as something I am finished with", so that the move
    // constructor is chosen instead of the copy constructor.

    // After a move, the old object is "moved-from": valid, but its contents
    // are no longer yours to rely on. Here it was left empty on purpose.
    std::println("  original now has {} readings (it was moved from)", original.size());

    std::println("\nmove assignment:");
    ReadingLog target{5};
    target = std::move(moved);
    std::println("  target has {} readings", target.size());

    std::println("\nreturning by value:");
    ReadingLog fresh{make_log(10)};
    std::println("  made a log of size {} with no copy or move line above", fresh.size());

    // What std::vector does when it runs out of room: it allocates bigger
    // storage and has to bring the old elements across. It MOVES them if the
    // move cannot throw (it keeps its strong guarantee: a failed move halfway
    // could not be undone), and otherwise falls back to COPYING.
    std::vector<Quiet> quiet;
    std::vector<Careless> careless;
    for (int i{0}; i < 8; ++i) {
        quiet.push_back(Quiet{});
        careless.push_back(Careless{});
    }

    std::println("\nvector growth, 8 push_backs each:");
    std::println("  Quiet    (noexcept move): {} copies, {} moves", quiet_copies, quiet_moves);
    std::println("  Careless (plain move):    {} copies, {} moves", careless_copies, careless_moves);

    static_assert(std::is_nothrow_move_constructible_v<Quiet>);
    static_assert(!std::is_nothrow_move_constructible_v<Careless>);

    return 0;
}
