#include <cstddef>
#include <flat_map>
#include <mdspan>
#include <print>
#include <string>
#include <vector>

// Two additions of C++23 to the containers family.
//
// COMPILER NOTE: <flat_map> and <mdspan> need GCC 15 or later (the course
// image has GCC 16), MSVC (current), or Clang with libc++. Clang with
// libstdc++ 14 does not have them: build with clang++ -stdlib=libc++.

int main() {

    // flat_map: the interface of std::map, a different layout. Instead of a
    // tree of nodes, two sorted vectors side by side.
    //
    //   std::map       node ─► node ─► node        pointers everywhere, one allocation per element
    //   std::flat_map  keys   [east north south]   contiguous
    //                  values [21.5 18.5  24.0 ]   contiguous
    //
    // Lookup is a binary search in a vector (cache friendly) and iterating is
    // as fast as iterating a vector. Inserting in the middle shifts elements,
    // like a vector. Good for tables that are built once and read many times.
    std::println("--- flat_map");
    std::flat_map<std::string, double> latest{
        {"south", 24.0}, {"north", 18.5}, {"east", 21.5}};      // sorted for you
    latest["west"] = 16.0;
    latest.insert_or_assign("north", 19.0);

    for (const auto& [station, temperature] : latest) {
        std::println("{:<6} {:5.1f}", station, temperature);
    }
    std::println("contains(east): {}   at(south): {}", latest.contains("east"), latest.at("south"));

    // The two vectors are visible, which is the point.
    std::println("keys() is a plain vector with {} elements", latest.keys().size());
    const auto& temperatures{latest.values()};
    std::println("first temperature in key order: {}", temperatures.front());

    // The iterators and references of a flat_map are invalidated like a vector's (14.4),
    // not like a map's. That is the price of the layout.

    // mdspan: a multi-dimensional VIEW onto data you already own, like
    // std::span (9.8) with rows and columns. It owns nothing and allocates nothing.
    std::println("\n--- mdspan");
    std::vector<double> data{
        18.5, 19.0, 21.5, 20.0,       // north: 4 readings
        24.0, 25.5, 26.0, 23.5,       // south
        16.0, 15.5, 17.0, 16.5};      // west
    std::mdspan grid{data.data(), 3, 4};                         // 3 rows, 4 columns

    std::println("rank {}, rows {}, columns {}, size {}", grid.rank(), grid.extent(0), grid.extent(1), grid.size());
    for (std::size_t row{0}; row < grid.extent(0); ++row) {
        for (std::size_t column{0}; column < grid.extent(1); ++column) {
            std::print("{:5.1f} ", grid[row, column]);        // the C++23 multi-index (12.6)
        }
        std::println();
    }

    // It is a view: writing through it changes the vector.
    grid[1, 2] = 99.0;
    std::println("data[6] is now {}", data[6]);

    // The LAYOUT says how (row, column) maps to a position in the flat data.
    // The default, layout_right, is row after row (C and C++ arrays).
    // layout_left is column after column (Fortran, many maths libraries).
    std::mdspan<double, std::dextents<std::size_t, 2>, std::layout_left> by_column{data.data(), 3, 4};
    std::println("\nthe same data, read by column: [0,1] is {} (default layout: {})",
                 by_column[0, 1], grid[0, 1]);

    // Sizes known at compile time can live in the type, so they cost nothing.
    std::mdspan<double, std::extents<std::size_t, 3, 4>> fixed{data.data()};
    std::println("fixed extents, sizeof the view: {} bytes (dynamic: {})", sizeof(fixed), sizeof(grid));
    return 0;
}
