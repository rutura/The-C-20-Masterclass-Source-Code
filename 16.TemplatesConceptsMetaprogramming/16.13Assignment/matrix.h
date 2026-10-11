#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <format>
#include <stdexcept>

// The Matrix of chapter 12, made generic. What changed, and why:
//
//   chapter 12                              this chapter
//   --------------------------------------  --------------------------------------------
//   cells are always double                 any number type: Matrix<int, ...>, Matrix<float, ...>
//   the shape is a run-time value           the shape is part of the TYPE: Matrix<double, 2, 3>
//   a wrong shape throws (chapter 13)       a wrong shape does not COMPILE
//   cells live in a std::vector (heap)      cells live in a std::array (inside the object)
//   operations run at run time              operations can run at compile time (constexpr)

// What a matrix may hold: the numbers of 16.8.
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T, std::size_t Rows, std::size_t Columns>
class Matrix {
public:
    static_assert(Rows > 0 && Columns > 0, "a Matrix needs at least one row and one column");

    using value_type = T;

    // All zeros.
    constexpr Matrix() = default;

    // Exactly Rows * Columns numbers, row by row:  Matrix<int, 2, 2> m{1, 2, 3, 4};
    // The count is checked by the constraint, so a wrong count does not compile (16.8, 16.10).
    // `explicit` keeps a single number from silently turning into a 1 x 1 matrix.
    template <typename... Values>
        requires (sizeof...(Values) == Rows * Columns && (std::convertible_to<Values, T> && ...))
    constexpr explicit Matrix(Values... values) : cells_{static_cast<T>(values)...} {}

    static constexpr Matrix filled(T value) {
        Matrix result;
        for (T& cell : result.cells_) {
            cell = value;
        }
        return result;
    }

    // Only a square matrix has an identity: the constraint (16.7) removes the
    // function for any other shape.
    static constexpr Matrix identity()
        requires (Rows == Columns)
    {
        Matrix result;
        for (std::size_t i{0}; i < Rows; ++i) {
            result[i, i] = T{1};
        }
        return result;
    }

    static constexpr std::size_t rows() { return Rows; }
    static constexpr std::size_t columns() { return Columns; }

    // matrix[row, column] (C++23, 12.6). Unchecked, like std::vector::operator[].
    constexpr T& operator[](std::size_t row, std::size_t column) {
        return cells_[row * Columns + column];
    }

    constexpr const T& operator[](std::size_t row, std::size_t column) const {
        return cells_[row * Columns + column];
    }

    // The checked version. The SHAPE can no longer be wrong, but an index
    // computed at run time still can be.
    constexpr const T& at(std::size_t row, std::size_t column) const {
        if (row >= Rows || column >= Columns) {
            throw std::out_of_range{"matrix index out of range"};
        }
        return cells_[row * Columns + column];
    }

    // Element-wise arithmetic. Both operands are Matrix<T, Rows, Columns>, so a
    // different shape is not a run-time error: it is a compile error.
    constexpr Matrix& operator+=(const Matrix& other) {
        for (std::size_t i{0}; i < cells_.size(); ++i) {
            cells_[i] += other.cells_[i];
        }
        return *this;
    }

    constexpr Matrix& operator-=(const Matrix& other) {
        for (std::size_t i{0}; i < cells_.size(); ++i) {
            cells_[i] -= other.cells_[i];
        }
        return *this;
    }

    constexpr Matrix& operator*=(T factor) {
        for (T& cell : cells_) {
            cell *= factor;
        }
        return *this;
    }

    friend constexpr Matrix operator+(Matrix left, const Matrix& right) {
        left += right;
        return left;
    }

    friend constexpr Matrix operator-(Matrix left, const Matrix& right) {
        left -= right;
        return left;
    }

    friend constexpr Matrix operator*(Matrix matrix, T factor) {
        matrix *= factor;
        return matrix;
    }

    friend constexpr Matrix operator*(T factor, Matrix matrix) {
        matrix *= factor;
        return matrix;
    }

    friend constexpr bool operator==(const Matrix&, const Matrix&) = default;

    // The rows and columns swap places, in the TYPE as well.
    constexpr Matrix<T, Columns, Rows> transposed() const {
        Matrix<T, Columns, Rows> result;
        for (std::size_t r{0}; r < Rows; ++r) {
            for (std::size_t c{0}; c < Columns; ++c) {
                result[c, r] = (*this)[r, c];
            }
        }
        return result;
    }

    constexpr T trace() const
        requires (Rows == Columns)
    {
        T total{};
        for (std::size_t i{0}; i < Rows; ++i) {
            total += (*this)[i, i];
        }
        return total;
    }

    // All the cells, row after row, so that range-for and the algorithms of
    // chapter 15 work on a Matrix.
    constexpr auto begin() { return cells_.begin(); }
    constexpr auto end() { return cells_.end(); }
    constexpr auto begin() const { return cells_.begin(); }
    constexpr auto end() const { return cells_.end(); }

private:
    std::array<T, Rows * Columns> cells_{};
};

// The matrix product: (Rows x Inner) times (Inner x Columns) is (Rows x Columns).
// Inner appears in BOTH parameters, so the compiler can only deduce it when the
// two shapes agree. Otherwise there is simply no operator* to call.
template <Number T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
constexpr Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, Inner>& left,
                                             const Matrix<T, Inner, Columns>& right) {
    Matrix<T, Rows, Columns> result;
    for (std::size_t r{0}; r < Rows; ++r) {
        for (std::size_t c{0}; c < Columns; ++c) {
            T sum{};
            for (std::size_t k{0}; k < Inner; ++k) {
                sum += left[r, k] * right[k, c];
            }
            result[r, c] = sum;
        }
    }
    return result;
}

// Printing with std::println: one row per line. This is a PARTIAL
// specialization of std::formatter (16.9): it covers every Matrix at once.
// As in 12.4, the format spec is handed to the formatter of the cell type, so
// {:6.1f} works for doubles and {:3} for ints.
template <typename T, std::size_t Rows, std::size_t Columns>
struct std::formatter<Matrix<T, Rows, Columns>> {
    std::formatter<T> cell;

    constexpr auto parse(std::format_parse_context& context) {
        return cell.parse(context);
    }

    auto format(const Matrix<T, Rows, Columns>& matrix, std::format_context& context) const {
        for (std::size_t r{0}; r < Rows; ++r) {
            context.advance_to(std::format_to(context.out(), "  ["));
            for (std::size_t c{0}; c < Columns; ++c) {
                context.advance_to(std::format_to(context.out(), " "));
                context.advance_to(cell.format(matrix[r, c], context));
            }
            context.advance_to(std::format_to(context.out(), " ]"));
            if (r + 1 < Rows) {
                context.advance_to(std::format_to(context.out(), "\n"));
            }
        }
        return context.out();
    }
};
