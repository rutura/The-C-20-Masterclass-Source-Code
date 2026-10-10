#pragma once

#include <cstddef>
#include <cstdint>

// The same two jobs as ops.asm, written in C++. They exist so that you can ask
// the compiler for ITS version of the assembly and compare it with yours.
int add_i32_cpp(int a, int b);
std::int64_t sum_array_cpp(const int* data, std::size_t count);
