module;

#include <cassert>

export module op_overloading_6;

namespace op_overloading_6{

    //Multi dimensional array subscript operator
    export class Array3d {
    private:
        static constexpr int X = 2;// Width
        static constexpr int Y = 3;// Depth
        static constexpr int Z = 4;// Height
        int m[X * Y * Z]{};

    public:
        // Multidimensional subscript operator for accessing elements (C++23)
        int& operator[](std::size_t z, std::size_t y, std::size_t x) {
            assert(x < X && y < Y && z < Z);
            return m[z * Y * X + y * X + x]; // Row major order. This is how the elements are stored in memory.
                                            // This formula is leant in your Linear Algebra class.
        }
    };
    
} // namespace op_overloading_6