#include <algorithm>
#include <cstddef>
#include <print>
#include <vector>

// A table of numbers with rows and columns, stored in ONE vector, row after
// row (the same trick as the pixel buffer of 6.17).
class Grid {
public:
    Grid(std::size_t rows, std::size_t columns)
        : rows_{rows}, columns_{columns}, cells_(rows * columns, 0.0) {}

    std::size_t rows() const { return rows_; }
    std::size_t columns() const { return columns_; }

    // C++23: the subscript operator may take MORE THAN ONE argument, so
    // grid[row, column] reads like the maths. Two versions, as in 10.5: one
    // for const grids (read only) and one for the rest (writable).
    double& operator[](std::size_t row, std::size_t column) {
        return cells_[row * columns_ + column];
    }

    const double& operator[](std::size_t row, std::size_t column) const {
        return cells_[row * columns_ + column];
    }

    // Before C++23 the same job was done with the CALL operator, grid(row,
    // column), because [] could take only one argument. Code in the wild is
    // full of it.
    double& operator()(std::size_t row, std::size_t column) {
        return cells_[row * columns_ + column];
    }

private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<double> cells_;
};

// A class that defines operator() is a FUNCTION OBJECT, or functor: an object
// you can call like a function, which also remembers things between calls.
class Offset {
public:
    explicit Offset(double amount) : amount_{amount} {}

    double operator()(double reading) const {
        return reading + amount_;
    }

private:
    double amount_;
};

// A functor with state that changes: it counts how often it was called.
class CountingScale {
public:
    explicit CountingScale(double factor) : factor_{factor} {}

    double operator()(double reading) {
        ++calls_;
        return reading * factor_;
    }

    int calls() const { return calls_; }

private:
    double factor_;
    int calls_{0};
};

int main() {

    Grid grid{2, 3};
    grid[0, 0] = 1.5;
    grid[1, 2] = 7.0;
    grid(0, 1) = 2.5;                         // the older spelling, same cell

    std::println("grid[0, 0] = {}, grid[0, 1] = {}, grid[1, 2] = {}", grid[0, 0], grid[0, 1], grid[1, 2]);

    const Grid& read_only{grid};
    std::println("through a const reference: {}", read_only[1, 2]);
    // read_only[1, 2] = 9.0;                 // error: the const overload returns a const reference

    // Neither version checks the indices, like the built-in [] and like
    // std::vector::operator[]. grid[5, 5] would be undefined behaviour.

    // A functor in use: apply it to a whole range with std::ranges::transform
    // (chapter 15). The algorithm just "calls it", and cannot tell it from a function.
    std::vector<double> readings{68.0, 71.5, 69.0};
    std::vector<double> calibrated(readings.size());
    std::ranges::transform(readings, calibrated.begin(), Offset{1.5});

    std::print("\ncalibrated: ");
    for (double reading : calibrated) {
        std::print("{} ", reading);
    }
    std::println("");

    // The functor remembers its state: how often it was called.
    CountingScale scale{2.0};
    scale(1.0);
    scale(2.0);
    scale(3.0);
    std::println("CountingScale was called {} times", scale.calls());

    // You have been using functors since 6.14: a LAMBDA is a functor that the
    // compiler writes for you. This lambda becomes, behind the scenes, a class
    // with an operator() very much like Offset.
    double amount{1.5};
    auto offset_lambda = [amount](double reading) { return reading + amount; };
    std::println("the lambda gives {} for 68, the Offset class gives {}", offset_lambda(68.0), Offset{1.5}(68.0));
    return 0;
}
