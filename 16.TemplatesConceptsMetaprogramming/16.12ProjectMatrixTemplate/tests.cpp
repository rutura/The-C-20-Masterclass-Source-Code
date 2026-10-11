#include <cmath>
#include <concepts>
#include <format>
#include <functional>
#include <print>
#include <source_location>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "matrix.h"

// The tests of chapter 13 for the Matrix of chapter 12 checked that wrong
// shapes THROW. Here the shapes are in the type, so there is nothing to throw:
// the mistakes do not compile, and the tests ask the compiler.
//
// Part 1 is checked while compiling. If this file builds, they all passed.
// Part 2 are ordinary run-time tests, with the small harness of 13.10.

using M22 = Matrix<double, 2, 2>;
using M23 = Matrix<double, 2, 3>;
using M32 = Matrix<double, 3, 2>;

// ---- Part 1: compile-time tests ----------------------------------------------

// "Does this expression compile?" asked as a concept (16.8).
template <typename A, typename B>
concept CanAdd = requires(A a, B b) { a + b; };

template <typename A, typename B>
concept CanMultiply = requires(A a, B b) { a * b; };

template <typename M>
concept HasIdentity = requires { M::identity(); };

// Shapes decide what is allowed.
static_assert(CanAdd<M23, M23>);
static_assert(!CanAdd<M23, M32>, "adding different shapes must not compile");
static_assert(CanMultiply<M23, M32>);
static_assert(CanMultiply<M32, M23>);
static_assert(!CanMultiply<M23, M23>, "(2 x 3) times (2 x 3) must not compile");
static_assert(HasIdentity<M22>);
static_assert(!HasIdentity<M23>, "a matrix that is not square has no identity");

// The count of numbers must match the shape.
static_assert(std::constructible_from<M22, double, double, double, double>);
static_assert(!std::constructible_from<M22, double, double, double>);
static_assert(!std::constructible_from<M22, double, double, double, double, double>);

// Only numbers can be cells.
template <typename T>
concept CanBeMatrix = requires { typename Matrix<T, 2, 2>; };
static_assert(CanBeMatrix<int>);
static_assert(CanBeMatrix<float>);
static_assert(!CanBeMatrix<std::string>, "a string is not a Number");

// The shape of a result is part of its type.
static_assert(std::same_as<decltype(M23{} * M32{}), M22>);
static_assert(std::same_as<decltype(M23{}.transposed()), M32>);

// And the arithmetic can be checked by the compiler itself.
constexpr Matrix<int, 2, 2> m{1, 2, 3, 4};
static_assert((m * m) == (Matrix<int, 2, 2>{7, 10, 15, 22}));
static_assert(m.transposed().transposed() == m);
static_assert(m.trace() == 5);
static_assert((m + m) == (2 * m));
static_assert((Matrix<int, 2, 2>::identity() * m) == m);

// ---- Part 2: run-time tests ----------------------------------------------------

int checks_run{0};
int checks_failed{0};
std::string current_test;

void check(bool condition, std::string_view expression,
           std::source_location where = std::source_location::current()) {
    ++checks_run;
    if (!condition) {
        ++checks_failed;
        std::println("  FAILED in {} (line {}): {}", current_test, where.line(), expression);
    }
}
#define CHECK(expression) check((expression), #expression)

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
    catch (...) {
    }
    ++checks_failed;
    std::println("  FAILED in {} (line {}): did not throw the expected exception", current_test, where.line());
}

void construction_is_row_by_row() {
    M23 a{1, 2, 3, 4, 5, 6};
    CHECK((a[0, 0] == 1.0 && a[0, 2] == 3.0 && a[1, 0] == 4.0 && a[1, 2] == 6.0));
    CHECK(a.rows() == 2);
    CHECK(a.columns() == 3);
}

void default_and_filled() {
    M22 zero;
    CHECK((zero[0, 0] == 0.0 && zero[1, 1] == 0.0));
    M22 sevens{M22::filled(7.0)};
    CHECK((sevens[0, 1] == 7.0 && sevens[1, 0] == 7.0));
}

void at_checks_the_index() {
    M22 a{1, 2, 3, 4};
    CHECK(a.at(1, 1) == 4.0);
    check_throws<std::out_of_range>([&] { (void)a.at(2, 0); });
    check_throws<std::out_of_range>([&] { (void)a.at(0, 2); });
}

void arithmetic() {
    M22 a{1, 2, 3, 4};
    M22 b{10, 20, 30, 40};
    CHECK((a + b == M22{11, 22, 33, 44}));
    CHECK((b - a == M22{9, 18, 27, 36}));
    CHECK((a * 2.0 == M22{2, 4, 6, 8}));
    CHECK((2.0 * a == a * 2.0));
}

void product_of_different_shapes() {
    M23 a{1, 2, 3, 4, 5, 6};
    M32 b{1, 0, 0, 1, 2, 2};
    CHECK((a * b == M22{7, 8, 16, 17}));
    CHECK((b * a).rows() == 3);
    CHECK((b * a).columns() == 3);
}

void identity_and_transpose() {
    CHECK((M22::identity() == M22{1, 0, 0, 1}));
    M23 a{1, 2, 3, 4, 5, 6};
    M32 t{a.transposed()};
    CHECK((t[2, 1] == 6.0 && t[0, 1] == 4.0));
}

void integers_work_too() {
    Matrix<int, 2, 2> a{1, 2, 3, 4};
    CHECK((a * a == Matrix<int, 2, 2>{7, 10, 15, 22}));
    CHECK(a.trace() == 5);
}

void cells_form_a_range() {
    M22 a{1, 2, 3, 4};
    double total{0.0};
    for (double cell : a) {
        total += cell;
    }
    CHECK(total == 10.0);
}

void floating_point_needs_a_tolerance() {
    Matrix<double, 1, 1> a{0.1};
    Matrix<double, 1, 1> b{0.2};
    auto sum{a + b};
    CHECK((sum[0, 0] != 0.3));                         // the trap (12.7); extra parentheses because of the comma (13.10)
    CHECK((std::abs(sum[0, 0] - 0.3) < 1e-9));
}

void formatter_follows_the_cell_type() {
    CHECK(std::format("{}", Matrix<int, 2, 2>{1, 2, 3, 4}) == "  [ 1 2 ]\n  [ 3 4 ]");
    CHECK(std::format("{:4}", Matrix<int, 1, 2>{1, 2}) == "  [    1    2 ]");
    CHECK(std::format("{:.1f}", M22{1, 2, 3, 4}) == "  [ 1.0 2.0 ]\n  [ 3.0 4.0 ]");
}

struct TestCase {
    std::string name;
    void (*body)();
};

int main() {
    std::vector<TestCase> tests{
        {"construction_is_row_by_row", construction_is_row_by_row},
        {"default_and_filled", default_and_filled},
        {"at_checks_the_index", at_checks_the_index},
        {"arithmetic", arithmetic},
        {"product_of_different_shapes", product_of_different_shapes},
        {"identity_and_transpose", identity_and_transpose},
        {"integers_work_too", integers_work_too},
        {"cells_form_a_range", cells_form_a_range},
        {"floating_point_needs_a_tolerance", floating_point_needs_a_tolerance},
        {"formatter_follows_the_cell_type", formatter_follows_the_cell_type},
    };

    int tests_failed{0};
    for (const auto& test : tests) {
        current_test = test.name;
        int failed_before{checks_failed};
        try {
            test.body();
        }
        catch (const std::exception& error) {
            ++checks_failed;
            std::println("  FAILED in {}: unexpected exception: {}", test.name, error.what());
        }
        bool passed{checks_failed == failed_before};
        tests_failed += passed ? 0 : 1;
        std::println("[{}] {}", passed ? " ok " : "FAIL", test.name);
    }

    std::println("\ncompile-time tests: passed (this file compiled)");
    std::println("{} run-time tests, {} failed; {} checks, {} failed", tests.size(), tests_failed, checks_run, checks_failed);
    return checks_failed == 0 ? 0 : 1;
}
