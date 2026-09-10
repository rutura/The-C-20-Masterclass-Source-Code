#include <array>
#include <print>

// A grid is "an array of rows", and each row is itself an array. So a
// 2D grid is std::array<std::array<T, columns>, rows>. The C-style
// `int grid[3][4];` is the same shape - this spelling just nests the
// type you already know.

constexpr std::size_t rows{3};
constexpr std::size_t columns{4};

using Grid = std::array<std::array<int, columns>, rows>;

// Take the grid by const reference: no copy of all 12 ints, and the
// function cannot modify the caller's grid.
void print_grid(const Grid& g) {
    for (const auto& row : g) {          // row is one std::array<int, 4>
        for (const auto& cell : row) {   // cell is one int
            std::print("{:4}", cell);
        }
        std::println("");
    }
}

int main() {
    // Nested braces mirror the nested type: three rows of four.
    Grid board{{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
    }};

    std::println("board:");
    print_grid(board);

    // Indexing is one [] per dimension: board[row][column].
    std::println("\nboard[1][2] = {}", board[1][2]);

    // Modify a cell in place, then a whole row via a reference.
    board[0][0] = 100;
    for (int& cell : board[2]) {
        cell *= 10;
    }

    std::println("\nafter edits:");
    print_grid(board);

    // Walk every cell with index math when you need the coordinates.
    int total{0};
    for (std::size_t r{0}; r < rows; ++r) {
        for (std::size_t c{0}; c < columns; ++c) {
            total += board[r][c];
        }
    }
    std::println("\nsum of all cells: {}", total);

    return 0;
}
