#include <print>

int main() {

    // 2D array
    // int packages[3][4]; // 12 ints worth of storage

    int packages[][4]{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {3, 4, 5, 6}};

    // Read data from a 2D array
    /*
    for (size_t i{0}; i < 3; ++i) {
        for (size_t j{0}; j < 4; ++j) {
            std::print("{}   ", packages[i][j]);
        }
        std::println("");
    }
    */

    // Use std::size to query the size of each dimension
    /*
    for (size_t i{0}; i < std::size(packages); ++i) {
        for (size_t j{0}; j < std::size(packages[i]); ++j) {
            std::print("{}   ", packages[i][j]);
        }
        std::println("");
    }
    */

    // 3D arrays follow the same pattern - just one more index.
    // 3 lights per room, 5 rooms per house, 7 houses per block.
    int house_block[7][5][3]{
        {
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}
        },
        {
            {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {25, 26, 27}, {28, 29, 30}
        },
        {
            {31, 32, 33}, {34, 35, 36}, {37, 38, 39}, {40, 41, 42}, {43, 44, 45}
        },
        {
            {46, 47, 48}, {49, 50, 51}, {52, 53, 54}, {55, 56, 57}, {58, 59, 60}
        },
        {
            {61, 62, 63}, {64, 65, 66}, {67, 68, 69}, {70, 71, 72}, {73, 74, 75}
        },
        {
            {76, 77, 78}, {79, 80, 81}, {82, 83, 84}, {85, 86, 87}, {88, 89, 90}
        },
        {
            {91, 92, 93}, {94, 95, 96}, {97, 98, 99}, {100, 101, 102}, {103, 104, 105}
        }};

    for (size_t i{0}; i < std::size(house_block); ++i) {
        for (size_t j{0}; j < std::size(house_block[i]); ++j) {
            for (size_t k{0}; k < std::size(house_block[i][j]); ++k) {
                std::print("{}     ", house_block[i][j][k]);
            }
        }
    }
    std::println("");

    // Omitting the leftmost dimension for a 2D array - only the leftmost
    // dimension can be left out; the compiler infers it from the
    // initializer list.
    /*
    int packages2[][3]{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {100, 110, 120} // add as many triplets as you want
    };

    std::println("");
    std::println("Omitting leftmost dimension for 2d array : ");
    for (size_t i{0}; i < std::size(packages2); ++i) {
        for (size_t j{0}; j < std::size(packages2[i]); ++j) {
            std::println("Item ({},{}) : {}", i, j, packages2[i][j]);
        }
    }
    */

    // For 3D (and any multi-dimensional array), every dimension except the
    // leftmost must be specified - omitting the 5 or the 3 below (or both)
    // is a compile error.
    /*
    int house_block1[][5][3]{
        {
            {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}
        },
        {
            {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {25, 26, 27}, {28, 29, 30}
        },
        {
            {31, 32, 33}, {34, 35, 36}, {37, 38, 39}, {40, 41, 42}, {43, 44, 45}
        },
        {
            {46, 47, 48}, {49, 50, 51}, {52, 53, 54}, {55, 56, 57}, {58, 59, 60}
        }};

    for (size_t i{0}; i < std::size(house_block1); ++i) {
        for (size_t j{0}; j < std::size(house_block1[i]); ++j) {
            std::print("[");
            for (size_t k{0}; k < std::size(house_block1[i][j]); ++k) {
                std::print("{} ", house_block1[i][j][k]);
            }
            std::print("] ");
        }
        std::println("");
    }
    */

    // If you supply fewer elements than a dimension's declared size, the
    // compiler fills the rest with 0 (or '\0' for char arrays).
    /*
    int house_block2[][5][4]{
        {
            {1, 2, 3}, {4}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15} // {4} auto-fills to {4,0,0,0}
        },
        {
            {16, 17, 18}, {19, 20, 21}, {22, 23, 24}, {25, 26, 27}, {28, 29, 30}
        },
        {
            {31, 32, 33}, {34, 35, 36}, {37, 38, 39}, {40, 41, 42}, {43, 44, 45}
        },
        {
            {46, 47, 48}, {49, 50, 51}, {52, 53, 54}, {55, 56, 57} // one row short - auto-fills with zeros
        }};

    house_block2[0][2][1] = 1021;

    std::println("");
    std::println("Printing out 3d house_block array with defaulted elements : ");
    for (size_t i{0}; i < std::size(house_block2); ++i) {
        for (size_t j{0}; j < std::size(house_block2[i]); ++j) {
            std::print("[");
            for (size_t k{0}; k < std::size(house_block2[i][j]); ++k) {
                std::print("{} ", house_block2[i][j][k]);
            }
            std::print("] ");
        }
        std::println("");
    }
    */

    return 0;
}
