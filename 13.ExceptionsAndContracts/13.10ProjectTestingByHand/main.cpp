#include <cmath>
#include <format>
#include <functional>
#include <print>
#include <source_location>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "matrix.h"

// ---------------------------------------------------------------------------
// A test framework in forty lines. Everything GoogleTest and Catch2 do
// starts from these ideas: run each test in isolation, record failures
// instead of stopping, report at the end, and tell the build whether it passed.
// ---------------------------------------------------------------------------

struct TestCase {
    std::string name;
    std::function<void()> body;
};

int checks_run{0};
int checks_failed{0};
std::string current_test;

void report_failure(std::string_view what, std::source_location where) {
    ++checks_failed;
    std::println("  FAILED in {} (line {}): {}", current_test, where.line(), what);
}

// A function with a source_location default argument sees the caller's line
// (13.8). The only reason for a macro is the text of the expression: only the
// preprocessor can turn `a == b` into the string "a == b".
void check(bool condition, std::string_view expression,
           std::source_location where = std::source_location::current()) {
    ++checks_run;
    if (!condition) {
        report_failure(expression, where);
    }
}
#define CHECK(expression) check((expression), #expression)

void check_near(double actual, double expected, double tolerance = 1e-9,
                std::source_location where = std::source_location::current()) {
    ++checks_run;
    if (std::abs(actual - expected) > tolerance) {
        report_failure(std::format("{} is not within {} of {}", actual, tolerance, expected), where);
    }
}

// The code under test goes in a lambda, so the framework can run it inside
// its own try block and tell "threw the right type" from "threw something
// else" and "did not throw".
template <typename Expected>
void check_throws(const std::function<void()>& code,
                  std::source_location where = std::source_location::current()) {
    ++checks_run;
    try {
        code();
    }
    catch (const Expected&) {
        return;
    }
    catch (const std::exception& error) {
        report_failure(std::format("threw a different exception: {}", error.what()), where);
        return;
    }
    report_failure("did not throw", where);
}

// ---------------------------------------------------------------------------
// The tests. One behaviour each, named for what they prove.
// ---------------------------------------------------------------------------

void construction_sets_shape_and_fill() {
    Matrix m{2, 3, 7.0};
    CHECK(m.rows() == 2);
    CHECK(m.columns() == 3);
    CHECK((m[1, 2] == 7.0));
}

void initializer_list_reads_row_by_row() {
    Matrix m{{1, 2, 3}, {4, 5, 6}};
    CHECK(m.rows() == 2);
    CHECK(m.columns() == 3);
    CHECK((m[0, 2] == 3.0));
    CHECK((m[1, 0] == 4.0));
}

void ragged_initializer_list_is_rejected() {
    check_throws<std::invalid_argument>([] { Matrix m{{1, 2}, {3}}; });
}

void identity_has_ones_on_the_diagonal() {
    Matrix i{Matrix::identity(3)};
    CHECK((i[0, 0] == 1.0 && i[1, 1] == 1.0 && i[2, 2] == 1.0));
    CHECK((i[0, 1] == 0.0 && i[2, 0] == 0.0));
}

void at_checks_the_index() {
    Matrix m{{1, 2}, {3, 4}};
    CHECK(m.at(1, 1) == 4.0);
    check_throws<std::out_of_range>([&] { m.at(2, 0); });
    check_throws<std::out_of_range>([&] { m.at(0, 2); });
}

void addition_subtraction_and_scaling() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{10, 20}, {30, 40}};
    CHECK((a + b == Matrix{{11, 22}, {33, 44}}));
    CHECK((b - a == Matrix{{9, 18}, {27, 36}}));
    CHECK((a * 2.0 == Matrix{{2, 4}, {6, 8}}));
    CHECK((2.0 * a == a * 2.0));
}

void adding_different_shapes_is_rejected() {
    Matrix a{2, 2};
    Matrix b{2, 3};
    check_throws<std::invalid_argument>([&] { a + b; });
    check_throws<std::invalid_argument>([&] { a += b; });
    check_throws<std::invalid_argument>([&] { a -= b; });
}

void matrix_product_multiplies_rows_by_columns() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};          // 2 x 3
    Matrix b{{1, 0}, {0, 1}, {2, 2}};        // 3 x 2
    CHECK((a * b == Matrix{{7, 8}, {16, 17}}));
    CHECK((a * Matrix::identity(3) == a));
}

void product_with_incompatible_shapes_is_rejected() {
    Matrix a{2, 3};
    check_throws<std::invalid_argument>([&] { a * a; });
}

void transposing_swaps_rows_and_columns() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix t{a.transposed()};
    CHECK(t.rows() == 3);
    CHECK(t.columns() == 2);
    CHECK((t[2, 1] == 6.0));
    CHECK(t.transposed() == a);
}

void equality_compares_shape_and_cells() {
    CHECK((Matrix{{1, 2}} == Matrix{{1, 2}}));
    CHECK((Matrix{{1, 2}} != Matrix{{1, 3}}));
    CHECK((Matrix{{1, 2}} != Matrix{{1}, {2}}));      // same cells, different shape
}

void floating_point_needs_a_tolerance() {
    Matrix a{{0.1}};
    Matrix b{{0.2}};
    Matrix sum{a + b};
    CHECK((sum[0, 0] != 0.3));                // the trap: 0.1 + 0.2 is not exactly 0.3
    check_near(sum[0, 0], 0.3);
}

void formatter_prints_one_row_per_line() {
    CHECK(std::format("{}", Matrix{{1, 2}, {3, 4}}) == "  [   1.0    2.0 ]\n  [   3.0    4.0 ]");
}

int main(int argc, char**) {

    std::vector<TestCase> tests{
        {"construction_sets_shape_and_fill", construction_sets_shape_and_fill},
        {"initializer_list_reads_row_by_row", initializer_list_reads_row_by_row},
        {"ragged_initializer_list_is_rejected", ragged_initializer_list_is_rejected},
        {"identity_has_ones_on_the_diagonal", identity_has_ones_on_the_diagonal},
        {"at_checks_the_index", at_checks_the_index},
        {"addition_subtraction_and_scaling", addition_subtraction_and_scaling},
        {"adding_different_shapes_is_rejected", adding_different_shapes_is_rejected},
        {"matrix_product_multiplies_rows_by_columns", matrix_product_multiplies_rows_by_columns},
        {"product_with_incompatible_shapes_is_rejected", product_with_incompatible_shapes_is_rejected},
        {"transposing_swaps_rows_and_columns", transposing_swaps_rows_and_columns},
        {"equality_compares_shape_and_cells", equality_compares_shape_and_cells},
        {"floating_point_needs_a_tolerance", floating_point_needs_a_tolerance},
        {"formatter_prints_one_row_per_line", formatter_prints_one_row_per_line},
    };

    // Run with any argument to watch a failing test being reported.
    if (argc > 1) {
        tests.push_back({"deliberately_wrong", [] {
            Matrix m{{1, 2}, {3, 4}};
            CHECK(m.rows() == 3);
            check_throws<std::out_of_range>([&] { m.transposed(); });
        }});
    }

    int tests_failed{0};
    for (const auto& test : tests) {
        current_test = test.name;
        int failed_before{checks_failed};
        try {
            test.body();
        }
        catch (const std::exception& error) {
            // An exception nobody expected is a failure, not a crash.
            report_failure(std::format("unexpected exception: {}", error.what()), std::source_location::current());
        }
        bool passed{checks_failed == failed_before};
        tests_failed += passed ? 0 : 1;
        std::println("[{}] {}", passed ? " ok " : "FAIL", test.name);
    }

    std::println("\n{} tests, {} failed; {} checks, {} failed",
                 tests.size(), tests_failed, checks_run, checks_failed);

    // The exit code is how the build system (CTest) learns the result.
    return checks_failed == 0 ? 0 : 1;
}
