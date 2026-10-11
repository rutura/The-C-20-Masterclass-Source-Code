#include <format>
#include <ostream>
#include <stdexcept>

#include <gtest/gtest.h>

#include "matrix.h"

// GoogleTest prints the two sides of a failed EXPECT_EQ. For types it does not
// know, it dumps raw bytes, which is useless. PrintTo teaches it to show a
// matrix the way 12.4 taught std::println to.
void PrintTo(const Matrix& matrix, std::ostream* out) {
    *out << "\n" << std::format("{}", matrix);
}

// A fixture: a class whose members are rebuilt before EVERY test that uses it.
// TEST_F creates a fresh MatrixTest per test, so tests cannot affect each other.
class MatrixTest : public testing::Test {
protected:
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
};

TEST(MatrixConstruction, SetsShapeAndFill) {
    Matrix m{2, 3, 7.0};
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.columns(), 3u);
    EXPECT_DOUBLE_EQ((m[1, 2]), 7.0);          // extra parentheses: the macro sees the comma
}

TEST(MatrixConstruction, InitializerListReadsRowByRow) {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    EXPECT_EQ(m.rows(), 2u);
    EXPECT_EQ(m.columns(), 3u);
    EXPECT_DOUBLE_EQ((m[0, 2]), 3.0);
    EXPECT_DOUBLE_EQ((m[1, 0]), 4.0);
}

TEST(MatrixConstruction, RaggedInitializerListIsRejected) {
    EXPECT_THROW((Matrix{{1, 2}, {3}}), std::invalid_argument);
}

TEST(MatrixConstruction, IdentityHasOnesOnTheDiagonal) {
    Matrix i{Matrix::identity(3)};
    EXPECT_DOUBLE_EQ((i[0, 0]), 1.0);
    EXPECT_DOUBLE_EQ((i[2, 2]), 1.0);
    EXPECT_DOUBLE_EQ((i[0, 1]), 0.0);
}

TEST_F(MatrixTest, AtChecksTheIndex) {
    EXPECT_DOUBLE_EQ(a.at(1, 1), 4.0);
    EXPECT_THROW(a.at(2, 0), std::out_of_range);
    EXPECT_THROW(a.at(0, 2), std::out_of_range);
}

TEST_F(MatrixTest, AdditionSubtractionAndScaling) {
    EXPECT_EQ(a + b, (Matrix{{11, 22}, {33, 44}}));
    EXPECT_EQ(b - a, (Matrix{{9, 18}, {27, 36}}));
    EXPECT_EQ(a * 2.0, (Matrix{{2, 4}, {6, 8}}));
    EXPECT_EQ(2.0 * a, a * 2.0);
}

TEST(MatrixErrors, AddingDifferentShapesIsRejected) {
    Matrix a{2, 2};
    Matrix b{2, 3};
    EXPECT_THROW(a + b, std::invalid_argument);
    EXPECT_THROW(a += b, std::invalid_argument);
    EXPECT_THROW(a -= b, std::invalid_argument);
}

TEST(MatrixProduct, MultipliesRowsByColumns) {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{1, 0}, {0, 1}, {2, 2}};
    EXPECT_EQ(a * b, (Matrix{{7, 8}, {16, 17}}));
    EXPECT_EQ(a * Matrix::identity(3), a);
}

TEST(MatrixErrors, ProductWithIncompatibleShapesIsRejected) {
    Matrix a{2, 3};
    EXPECT_THROW(a * a, std::invalid_argument);
}

TEST(MatrixTranspose, SwapsRowsAndColumns) {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix t{a.transposed()};
    EXPECT_EQ(t.rows(), 3u);
    EXPECT_EQ(t.columns(), 2u);
    EXPECT_DOUBLE_EQ((t[2, 1]), 6.0);
    EXPECT_EQ(t.transposed(), a);
}

TEST(MatrixEquality, ComparesShapeAndCells) {
    EXPECT_EQ((Matrix{{1, 2}}), (Matrix{{1, 2}}));
    EXPECT_NE((Matrix{{1, 2}}), (Matrix{{1, 3}}));
    EXPECT_NE((Matrix{{1, 2}}), (Matrix{{1}, {2}}));
}

TEST(MatrixFloatingPoint, NeedsATolerance) {
    Matrix sum{Matrix{{0.1}} + Matrix{{0.2}}};
    EXPECT_NE((sum[0, 0]), 0.3);                 // the trap
    EXPECT_DOUBLE_EQ((sum[0, 0]), 0.3);          // compares within 4 ULPs
    EXPECT_NEAR((sum[0, 0]), 0.3, 1e-9);
}

TEST(MatrixFormatter, PrintsOneRowPerLine) {
    EXPECT_EQ(std::format("{}", Matrix{{1, 2}, {3, 4}}), "  [   1.0    2.0 ]\n  [   3.0    4.0 ]");
}

// Remove the comment markers to watch a failure being reported:
// TEST(Demo, DeliberatelyWrong) {
//     Matrix m{{1, 2}, {3, 4}};
//     EXPECT_EQ(m, (Matrix{{1, 2}, {3, 5}}));
// }
