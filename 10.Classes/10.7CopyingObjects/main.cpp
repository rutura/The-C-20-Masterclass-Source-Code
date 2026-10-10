#include <algorithm>
#include <cstddef>
#include <print>

// First, the BUG, in a form that is safe to run. This struct has a raw pointer
// and no copy code of its own, so the compiler writes a copy that copies the
// POINTER and nothing else. (There is deliberately no destructor: add one and
// the program would delete the same block twice.)
struct ShallowLog {
    double* data;
    std::size_t size;
};

// Now the real class: it owns its block, so a copy must make its OWN block.
class ReadingLog {
public:
    explicit ReadingLog(std::size_t capacity)
        : data_{new double[capacity]{}}, capacity_{capacity} {}

    // The copy constructor: builds a new log from an existing one. A DEEP
    // copy: a fresh block of the same size, then every element copied across.
    ReadingLog(const ReadingLog& other)
        : data_{new double[other.capacity_]}, capacity_{other.capacity_}, size_{other.size_} {
        std::copy_n(other.data_, other.size_, data_);
        std::println("  copy constructed (a new block of {})", capacity_);
    }

    // The copy assignment operator: replaces what THIS log holds with a copy
    // of another. It must cope with an existing block, and with "a = a".
    ReadingLog& operator=(const ReadingLog& other) {
        std::println("  copy assigned");
        if (this == &other) {
            return *this;                       // self-assignment: nothing to do
        }

        double* fresh{new double[other.capacity_]};    // allocate FIRST: if this throws, *this is untouched
        std::copy_n(other.data_, other.size_, fresh);

        delete[] data_;                         // only now give the old block back
        data_ = fresh;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }

    ~ReadingLog() {
        delete[] data_;
    }

    bool add(double reading) {
        if (size_ == capacity_) {
            return false;
        }
        data_[size_++] = reading;
        return true;
    }

    double at(std::size_t index) const { return data_[index]; }
    void set(std::size_t index, double value) { data_[index] = value; }
    std::size_t size() const { return size_; }
    const double* address() const { return data_; }

private:
    double* data_;
    std::size_t capacity_;
    std::size_t size_{0};
};

// A by-value parameter is a COPY: the copy constructor runs on every call.
double first_of(ReadingLog log) {
    return log.at(0);
}

// A const reference is not: no copy, no cost.
double first_of_ref(const ReadingLog& log) {
    return log.at(0);
}

int main() {

    std::println("the compiler's own copy of a struct with a pointer:");
    ShallowLog original{new double[3]{60.0, 61.0, 62.0}, 3};
    ShallowLog copy{original};                    // copies the pointer, not the data
    copy.data[0] = 99.0;
    std::println("  original.data[0] = {}  (we changed the COPY)", original.data[0]);
    std::println("  same block: {}", original.data == copy.data);
    delete[] original.data;                       // one block, one delete

    std::println("\na class with a proper deep copy:");
    ReadingLog first{3};
    first.add(60.0);
    first.add(61.0);
    first.add(62.0);

    ReadingLog second{first};                     // copy constructor
    second.set(0, 99.0);
    std::println("  first.at(0) = {}, second.at(0) = {}", first.at(0), second.at(0));
    std::println("  same block: {}", first.address() == second.address());

    ReadingLog third{1};
    third = first;                                // copy assignment
    std::println("  third now has {} readings, third.at(2) = {}", third.size(), third.at(2));

    third = third;                                // self-assignment is safe

    std::println("\nwhen copies happen, without you writing the word \"copy\":");
    std::println("  passing by value:");
    first_of(first);
    std::println("  passing by const reference:");
    first_of_ref(first);

    // Copying is part of what a class "means". The rule that follows: if a
    // class owns a resource, ask yourself what copying it should do, and
    // write that down, or forbid it (10.9).
    return 0;
}
