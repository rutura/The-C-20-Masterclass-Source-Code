#include <array>
#include <cstddef>
#include <print>

// A template parameter does not have to be a type. It can be a VALUE, known at
// compile time. You have used this already: in std::array<int, 6> the 6 is such
// a value, and it is part of the type (7.2). Here is how to write one.

// A buffer for at most N readings, with no heap allocation: the room is part of
// the object, like a std::array. T is a type parameter, N is a value parameter.
template <typename T, std::size_t N>
class Buffer {
public:
    // A mistake in the template arguments is reported when the class is made.
    static_assert(N > 0, "a Buffer must have room for at least one value");

    bool push(const T& value) {
        if (size_ == N) {
            return false;                          // full: refuse
        }
        items_[size_] = value;
        ++size_;
        return true;
    }

    std::size_t size() const { return size_; }
    constexpr std::size_t capacity() const { return N; }
    bool full() const { return size_ == N; }

private:
    std::array<T, N> items_{};
    std::size_t size_{0};
};

// A value parameter can have a default, like a type parameter.
template <typename T, std::size_t N = 8>
class Window {
public:
    constexpr std::size_t length() const { return N; }
};

// A grid whose SHAPE is part of its type. Grid<double, 2, 3> and
// Grid<double, 3, 2> are different types. The next lecture's project, the
// Matrix, is built on exactly this.
template <typename T, std::size_t Rows, std::size_t Columns>
class Grid {
public:
    T& operator[](std::size_t row, std::size_t column) { return cells_[row * Columns + column]; }
    const T& operator[](std::size_t row, std::size_t column) const { return cells_[row * Columns + column]; }

    static constexpr std::size_t rows() { return Rows; }
    static constexpr std::size_t columns() { return Columns; }

private:
    std::array<T, Rows * Columns> cells_{};        // an expression of the parameters, computed by the compiler
};

// Addition is defined only for two grids of the SAME shape: the same Rows and
// Columns appear in both parameters, so the compiler checks it for us.
template <typename T, std::size_t Rows, std::size_t Columns>
Grid<T, Rows, Columns> add(const Grid<T, Rows, Columns>& a, const Grid<T, Rows, Columns>& b) {
    Grid<T, Rows, Columns> result;
    for (std::size_t r{0}; r < Rows; ++r) {
        for (std::size_t c{0}; c < Columns; ++c) {
            result[r, c] = a[r, c] + b[r, c];
        }
    }
    return result;
}

// The compiler can DEDUCE a value parameter, too: N comes from the std::array
// that is passed in. There is no size argument to get wrong.
template <typename T, std::size_t N>
T sum_of(const std::array<T, N>& values) {
    T total{};
    for (const T& value : values) {
        total += value;
    }
    return total;
}

// A function that accepts only a Buffer of exactly four ints.
void report(const Buffer<int, 4>& buffer) {
    std::println("a Buffer<int, 4> holding {} of {}", buffer.size(), buffer.capacity());
}

int main() {

    std::println("--- a value as a template parameter");
    Buffer<int, 4> counts;
    for (int value : {10, 20, 30, 40, 50}) {
        bool accepted{counts.push(value)};
        std::println("push({}): {}", value, accepted ? "stored" : "refused, the buffer is full");
    }
    report(counts);

    Buffer<double, 128> big;                       // a different type: room for 128
    std::println("Buffer<double, 128> has capacity {} and holds {}", big.capacity(), big.size());
    // report(big);                                // error: not a Buffer<int, 4>
    // Buffer<int, 0> nothing;                     // error: "a Buffer must have room for at least one value"

    std::println("\n--- the value is part of the type: the room is inside the object, nothing is allocated");
    std::println("sizeof(Buffer<char, 4>)   = {}", sizeof(Buffer<char, 4>));
    std::println("sizeof(Buffer<char, 100>) = {}", sizeof(Buffer<char, 100>));

    std::println("\n--- a default value");
    Window<double> usual;                          // N = 8
    Window<double, 24> day;
    std::println("usual window: {}   day window: {}", usual.length(), day.length());

    // The value is known to the compiler, so it can be used where only constants
    // are allowed: here, in a static_assert (13.9).
    static_assert(Buffer<int, 4>{}.capacity() == 4);

    std::println("\n--- a shape in the type");
    Grid<double, 2, 3> a;
    Grid<double, 2, 3> b;
    for (std::size_t r{0}; r < a.rows(); ++r) {
        for (std::size_t c{0}; c < a.columns(); ++c) {
            a[r, c] = static_cast<double>(r * 10 + c);
            b[r, c] = 1.0;
        }
    }
    auto sum{add(a, b)};
    std::println("sum[1, 2] = {}   shape {} x {}", sum[1, 2], sum.rows(), sum.columns());
    // Grid<double, 3, 2> tall;
    // add(a, tall);                               // error at compile time: the shapes do not match

    std::println("\n--- deduced from a std::array");
    std::array<int, 4> hours{6, 12, 18, 24};
    std::array<double, 3> readings{18.5, 24.0, 21.5};
    std::println("sum_of(hours) = {}   sum_of(readings) = {}", sum_of(hours), sum_of(readings));
    return 0;
}
