#include <format>
#include <stdexcept>
#include <string>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "matrix.h"

// Catch2 prints values that appear in a failed check. For a type it does not
// know it prints "{?}". StringMaker is the hook that teaches it, here by
// reusing the std::formatter written in 12.4.
template <>
struct Catch::StringMaker<Matrix> {
    static std::string convert(const Matrix& matrix) {
        return "\n" + std::format("{}", matrix);
    }
};

// Catch2 has no fixtures. A test case is a function, and a SECTION inside it
// is a branch: the test case runs once PER SECTION, from the top, so the
// setup lines above a section are redone fresh for each one.
TEST_CASE("Matrix construction", "[matrix]") {
    SECTION("sets shape and fill") {
        Matrix m{2, 3, 7.0};
        CHECK(m.rows() == 2);
        CHECK(m.columns() == 3);
        CHECK((m[1, 2] == 7.0));
    }

    SECTION("an initializer list is read row by row") {
        Matrix m{{1, 2, 3}, {4, 5, 6}};
        CHECK(m.rows() == 2);
        CHECK(m.columns() == 3);
        CHECK((m[0, 2] == 3.0));
        CHECK((m[1, 0] == 4.0));
    }

    SECTION("a ragged initializer list is rejected") {
        CHECK_THROWS_AS((Matrix{{1, 2}, {3}}), std::invalid_argument);
    }

    SECTION("identity has ones on the diagonal") {
        Matrix i{Matrix::identity(3)};
        CHECK((i[0, 0] == 1.0));
        CHECK((i[2, 2] == 1.0));
        CHECK((i[0, 1] == 0.0));
    }
}

TEST_CASE("Matrix arithmetic", "[matrix]") {
    // Runs again for every SECTION below.
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};

    SECTION("addition, subtraction and scaling") {
        CHECK(a + b == Matrix{{11, 22}, {33, 44}});
        CHECK(b - a == Matrix{{9, 18}, {27, 36}});
        CHECK(a * 2.0 == Matrix{{2, 4}, {6, 8}});
        CHECK(2.0 * a == a * 2.0);
    }

    SECTION("different shapes are rejected") {
        Matrix wide{2, 3};
        CHECK_THROWS_AS(a + wide, std::invalid_argument);
        CHECK_THROWS_AS(a += wide, std::invalid_argument);
        CHECK_THROWS_AS(a -= wide, std::invalid_argument);
        // The message is part of the behaviour too.
        CHECK_THROWS_WITH(a + wide, "matrices must have the same shape");
    }

    SECTION("the matrix product multiplies rows by columns") {
        Matrix m{{1, 2, 3}, {4, 5, 6}};
        Matrix n{{1, 0}, {0, 1}, {2, 2}};
        CHECK(m * n == Matrix{{7, 8}, {16, 17}});
        CHECK(m * Matrix::identity(3) == m);
        CHECK_THROWS_AS(m * m, std::invalid_argument);
    }
}

TEST_CASE("Matrix access", "[matrix]") {
    Matrix m{{1, 2}, {3, 4}};

    CHECK(m.at(1, 1) == 4.0);
    CHECK_THROWS_AS(m.at(2, 0), std::out_of_range);
    CHECK_THROWS_AS(m.at(0, 2), std::out_of_range);
}

TEST_CASE("Matrix transpose and equality", "[matrix]") {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix t{a.transposed()};

    CHECK(t.rows() == 3);
    CHECK(t.columns() == 2);
    CHECK((t[2, 1] == 6.0));
    CHECK(t.transposed() == a);

    CHECK(Matrix{{1, 2}} == Matrix{{1, 2}});
    CHECK(Matrix{{1, 2}} != Matrix{{1, 3}});
    CHECK(Matrix{{1, 2}} != Matrix{{1}, {2}});
}

TEST_CASE("Matrix floating point needs a tolerance", "[matrix]") {
    Matrix sum{Matrix{{0.1}} + Matrix{{0.2}}};

    CHECK((sum[0, 0] != 0.3));                                          // the trap
    CHECK((sum[0, 0] == Catch::Approx(0.3)));                           // relative tolerance
    CHECK_THAT((sum[0, 0]), Catch::Matchers::WithinAbs(0.3, 1e-9));     // absolute tolerance
}

TEST_CASE("Matrix formatter", "[matrix][format]") {
    CHECK(std::format("{}", Matrix{{1, 2}, {3, 4}}) == "  [   1.0    2.0 ]\n  [   3.0    4.0 ]");
}

// Remove the comment markers to watch a failure being reported:
// TEST_CASE("Demo", "[.]") {
//     Matrix m{{1, 2}, {3, 4}};
//     CHECK(m == Matrix{{1, 2}, {3, 5}});
// }
