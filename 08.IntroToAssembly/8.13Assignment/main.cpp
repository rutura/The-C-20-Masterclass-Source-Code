#include <cstddef>
#include <cstdint>
#include <format>
#include <print>
#include <string>
#include <string_view>
#include <vector>

/*
    Chapter 8 assignment - Intro to assembly

    You write functions in assembly, this file checks them. Exercises 1 to 5
    are in exercises.asm, exercise 6 is in mystery.cpp, exercise 7 needs no
    code. Statements and hints sit above each stub.

    Run it inside the Linux container (see 8.12). From this folder:

        apt-get update && apt-get install -y nasm      # once per container
        cmake -S . -B build -G Ninja -DCMAKE_CXX_COMPILER=g++
        cmake --build build
        ./build/rooster                # your answers
        ./build/rooster_solution       # the solved version, for comparison

    Every line ends in "ok" or "FAIL". The program returns 0 only when
    everything passes.

    Exercise 7 - the debugger (no code). Build rooster_solution, then:

        gdb ./build/rooster_solution
        (gdb) set disassembly-flavor intel
        (gdb) break factorial
        (gdb) run
        (gdb) stepi            (repeat; after each step, print rax and rcx
        (gdb) info registers rax rcx           with this command)

    Watch rax grow while rcx counts down. Write down, from what you see, the
    value of rax after the third pass through the loop of factorial(5).
*/

// Defined in exercises.asm. extern "C" because the assembler does not mangle.
extern "C" {
    int abs_i32(int x);
    int max_i32(int a, int b);
    std::size_t count_above(const int* data, std::size_t count, int threshold);
    std::uint64_t factorial(unsigned n);
    int sum_to(int n);
    int mystery(int n);
}

// Defined in mystery.cpp, written by you.
int mystery_cpp(int n);

int failures{0};

template <typename T>
void expect(std::string_view call, T actual, T expected) {
    const bool passed{actual == expected};
    if (!passed) {
        ++failures;
    }
    std::println("  {:<34} = {:<20} {}", call, actual,
                 passed ? "ok" : std::format("FAIL, expected {}", expected));
}

int main() {

    std::println("--- Exercise 1: abs_i32 ---");
    expect("abs_i32(-5)", abs_i32(-5), 5);
    expect("abs_i32(7)", abs_i32(7), 7);
    expect("abs_i32(0)", abs_i32(0), 0);

    std::println("--- Exercise 2: max_i32 ---");
    expect("max_i32(3, 9)", max_i32(3, 9), 9);
    expect("max_i32(9, 3)", max_i32(9, 3), 9);
    expect("max_i32(-4, -8)", max_i32(-4, -8), -4);
    expect("max_i32(5, 5)", max_i32(5, 5), 5);

    std::println("--- Exercise 3: count_above ---");
    const std::vector<int> readings{68, 72, 59, 81, 90, 55, 77, 64};
    expect("count_above(readings, 70)",
           count_above(readings.data(), readings.size(), 70), std::size_t{4});
    expect("count_above(readings, 100)",
           count_above(readings.data(), readings.size(), 100), std::size_t{0});
    expect("count_above(readings, 0)",
           count_above(readings.data(), readings.size(), 0), std::size_t{8});
    expect("count_above(readings, count 0)",
           count_above(readings.data(), 0, 0), std::size_t{0});

    std::println("--- Exercise 4: factorial ---");
    expect("factorial(0)", factorial(0), std::uint64_t{1});
    expect("factorial(5)", factorial(5), std::uint64_t{120});
    expect("factorial(10)", factorial(10), std::uint64_t{3'628'800});
    expect("factorial(20)", factorial(20), std::uint64_t{2'432'902'008'176'640'000});

    std::println("--- Exercise 5: sum_to ---");
    expect("sum_to(0)", sum_to(0), 0);
    expect("sum_to(1)", sum_to(1), 1);
    expect("sum_to(10)", sum_to(10), 55);
    expect("sum_to(100)", sum_to(100), 5050);
    expect("sum_to(-3)", sum_to(-3), 0);

    std::println("--- Exercise 6: mystery_cpp against mystery ---");
    int mismatches{0};
    for (int n{-6}; n <= 12; ++n) {
        if (mystery_cpp(n) != mystery(n)) {
            ++mismatches;
            std::println("  n = {:>3}: asm says {}, your C++ says {}", n, mystery(n), mystery_cpp(n));
        }
    }
    if (mismatches == 0) {
        std::println("  all 19 inputs agree   ok");
    } else {
        ++failures;
    }

    std::println("");
    if (failures == 0) {
        std::println("All exercises passed.");
    } else {
        std::println("{} check(s) failed.", failures);
    }

    return failures == 0 ? 0 : 1;
}
