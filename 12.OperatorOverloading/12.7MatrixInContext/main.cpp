#include <print>
#include <utility>

#include "matrix.h"

// This lecture is about using the Matrix, and about what operators have to do
// with cost. Read matrix.h first: every operator in it was introduced in 12.2
// to 12.6.

int main() {

    Matrix a{{1.0, 2.0, 3.0},
             {4.0, 5.0, 6.0}};                  // 2 x 3
    Matrix b{{1.0, 0.0},
             {0.0, 1.0},
             {2.0, 2.0}};                       // 3 x 2

    std::println("a (2 x 3):\n{}", a);
    std::println("\nb (3 x 2):\n{}", b);

    // Operators make the maths read like the maths.
    Matrix product{a * b};                      // (2 x 3) times (3 x 2) = 2 x 2
    std::println("\na * b (2 x 2):\n{}", product);

    std::println("\na transposed (3 x 2):\n{}", a.transposed());

    // Scalars work in both orders (12.3), and compound assignment in place.
    Matrix scaled{2.0 * a};
    scaled -= a;
    std::println("\n2 * a - a == a: {}", scaled == a);

    // The identity matrix changes nothing when you multiply by it.
    Matrix identity{Matrix::identity(3)};
    std::println("a * identity == a: {}", a * identity == a);

    // Copying and moving come free (the rule of zero): the class has no
    // special member functions at all, and the vector inside does the work.
    Matrix copy{a};
    copy[0, 0] = 99.0;
    std::println("\nafter changing the copy: a[0, 0] = {}, copy[0, 0] = {}", a[0, 0], copy[0, 0]);

    Matrix moved{std::move(copy)};
    std::println("moved has {} x {}", moved.rows(), moved.columns());

    // COST. Every binary operator returns a NEW matrix, so a long expression
    // creates temporaries, each one a new vector allocated and then freed:
    //
    //     Matrix result{a + b + c + d};       // three temporaries
    //
    // When it matters (large matrices, in a loop), build the result in place
    // with the compound operators, which allocate nothing:
    //
    //     Matrix result{a};
    //     result += b;
    //     result += c;
    //     result += d;
    //
    // The operators in matrix.h do exactly this internally (operator+ is built
    // from +=), so you pay for the one copy of the left operand and no more.

    // And when the operation cannot be done, the operator says so loudly
    // instead of returning nonsense. This line is commented out because it
    // throws; chapter 13 shows how to catch it, and chapter 13's project
    // writes tests that check for it:
    //     Matrix wrong{a + b};                // throws std::invalid_argument: shapes differ
    return 0;
}
