#include "reference.h"

int add_i32_cpp(int a, int b) {
    return a + b;
}

std::int64_t sum_array_cpp(const int* data, std::size_t count) {
    std::int64_t total{0};
    for (std::size_t i{0}; i < count; ++i) {
        total += data[i];
    }
    return total;
}
