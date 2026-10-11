#pragma once

#include <cstddef>
#include <format>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// A rectangular grid of doubles, with the arithmetic of linear algebra.
//
// It is the chapter's main class, and chapters 13 and 16 build on it. Look at
// what it does NOT contain: no destructor, no copy constructor, no move
// operations. The data lives in a std::vector, so the compiler-written versions
// are exactly right (the rule of zero, 10.9).
//
// Operations that cannot be done (adding two matrices of different sizes)
// throw an exception. Exceptions are chapter 13. For now, read "throw" as "stop
// here and report the mistake loudly".
class Matrix {
public:
    Matrix(std::size_t rows, std::size_t columns, double fill = 0.0)
        : rows_{rows}, columns_{columns}, cells_(rows * columns, fill) {}

    // A matrix written out row by row: Matrix{{1, 2}, {3, 4}}.
    Matrix(std::initializer_list<std::initializer_list<double>> rows)
        : rows_{rows.size()}, columns_{rows.size() == 0 ? 0 : rows.begin()->size()} {
        cells_.reserve(rows_ * columns_);
        for (const auto& row : rows) {
            if (row.size() != columns_) {
                throw std::invalid_argument{"every row must have the same number of columns"};
            }
            cells_.insert(cells_.end(), row.begin(), row.end());
        }
    }

    // The identity matrix: ones on the diagonal, zeros everywhere else.
    static Matrix identity(std::size_t size) {
        Matrix result{size, size};
        for (std::size_t i{0}; i < size; ++i) {
            result[i, i] = 1.0;
        }
        return result;
    }

    std::size_t rows() const { return rows_; }
    std::size_t columns() const { return columns_; }

    // matrix[row, column] (C++23). Unchecked, like std::vector::operator[].
    double& operator[](std::size_t row, std::size_t column) {
        return cells_[row * columns_ + column];
    }

    const double& operator[](std::size_t row, std::size_t column) const {
        return cells_[row * columns_ + column];
    }

    // The checked version: throws instead of reading outside the matrix.
    double at(std::size_t row, std::size_t column) const {
        if (row >= rows_ || column >= columns_) {
            throw std::out_of_range{"matrix index out of range"};
        }
        return cells_[row * columns_ + column];
    }

    // Compound assignment first: it is the real work, and it creates no temporary.
    Matrix& operator+=(const Matrix& other) {
        require_same_shape(other);
        for (std::size_t i{0}; i < cells_.size(); ++i) {
            cells_[i] += other.cells_[i];
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        require_same_shape(other);
        for (std::size_t i{0}; i < cells_.size(); ++i) {
            cells_[i] -= other.cells_[i];
        }
        return *this;
    }

    Matrix& operator*=(double factor) {
        for (double& cell : cells_) {
            cell *= factor;
        }
        return *this;
    }

    // The binary operators, built from them. The left operand is taken by
    // value, so it is already the copy to modify and return.
    friend Matrix operator+(Matrix left, const Matrix& right) {
        left += right;
        return left;
    }

    friend Matrix operator-(Matrix left, const Matrix& right) {
        left -= right;
        return left;
    }

    friend Matrix operator*(Matrix matrix, double factor) {
        matrix *= factor;
        return matrix;
    }

    friend Matrix operator*(double factor, Matrix matrix) {
        matrix *= factor;
        return matrix;
    }

    // The matrix product: (a x b) times (b x c) is (a x c). Not a cell-by-cell
    // product: each result cell is a row of the left times a column of the right.
    friend Matrix operator*(const Matrix& left, const Matrix& right) {
        if (left.columns_ != right.rows_) {
            throw std::invalid_argument{"columns of the left matrix must equal rows of the right"};
        }
        Matrix result{left.rows_, right.columns_};
        for (std::size_t r{0}; r < left.rows_; ++r) {
            for (std::size_t c{0}; c < right.columns_; ++c) {
                double sum{0.0};
                for (std::size_t k{0}; k < left.columns_; ++k) {
                    sum += left[r, k] * right[k, c];
                }
                result[r, c] = sum;
            }
        }
        return result;
    }

    Matrix transposed() const {
        Matrix result{columns_, rows_};
        for (std::size_t r{0}; r < rows_; ++r) {
            for (std::size_t c{0}; c < columns_; ++c) {
                result[c, r] = (*this)[r, c];
            }
        }
        return result;
    }

    // Two matrices are equal when they have the same shape and the same cells.
    // (Comparing doubles for exact equality is risky after arithmetic: see the
    // note in 12.7 about tolerances.)
    friend bool operator==(const Matrix&, const Matrix&) = default;

private:
    void require_same_shape(const Matrix& other) const {
        if (rows_ != other.rows_ || columns_ != other.columns_) {
            throw std::invalid_argument{"matrices must have the same shape"};
        }
    }

    std::size_t rows_;
    std::size_t columns_;
    std::vector<double> cells_;
};

// Printing a matrix with std::println: one row per line.
template <>
struct std::formatter<Matrix> {
    constexpr auto parse(std::format_parse_context& context) {
        return context.begin();
    }

    auto format(const Matrix& matrix, std::format_context& context) const {
        auto out{context.out()};
        for (std::size_t r{0}; r < matrix.rows(); ++r) {
            out = std::format_to(out, "  [");
            for (std::size_t c{0}; c < matrix.columns(); ++c) {
                out = std::format_to(out, "{}{:6.1f}", c == 0 ? "" : " ", matrix[r, c]);
            }
            out = std::format_to(out, " ]{}", r + 1 < matrix.rows() ? "\n" : "");
        }
        return out;
    }
};
