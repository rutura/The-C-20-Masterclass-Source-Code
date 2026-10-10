#include <cstddef>
#include <cstdint>
#include <print>
#include <vector>

#include "reference.h"

// PROJECT: call functions that were written in assembly, not in C++.
//
// add_i32 and sum_array live in ops.asm. The C++ compiler never sees their
// bodies: it only sees these two declarations, and trusts them. The linker
// joins ops.o to the rest, exactly as in 7.12.
//
// extern "C" switches name mangling OFF for these declarations. The object
// file made from ops.asm contains the plain names add_i32 and sum_array, and
// without extern "C" the compiler would ask the linker for something like
// _Z7add_i32ii instead (see 7.12), which does not exist.
extern "C" {
    int add_i32(int a, int b);
    std::int64_t sum_array(const int* data, std::size_t count);
}

int main() {

    const std::vector<int> readings{68, 72, 59, 81, 90, 55, 77, 64};

    std::println("add_i32(20, 22)      asm: {}   c++: {}",
                 add_i32(20, 22), add_i32_cpp(20, 22));

    std::println("sum_array(readings)  asm: {}  c++: {}",
                 sum_array(readings.data(), readings.size()),
                 sum_array_cpp(readings.data(), readings.size()));

    return 0;
}
