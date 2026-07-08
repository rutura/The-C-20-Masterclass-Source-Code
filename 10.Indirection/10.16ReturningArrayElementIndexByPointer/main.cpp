#include <print>

const double* find_max_address(const double scores[], size_t count);

int main() {

    double array[]{1.0, 2.0, 3.0, 45.0, 5.0, 6.0, 7.0, 8.0, 79.0, 10.0};
    const double* p_max = find_max_address(array, std::size(array));
    std::println("max : {}", *p_max);

    return 0;
}

const double* find_max_address(const double scores[], size_t count) {

    size_t max_index{};
    double max{};

    for (size_t i{0}; i < count; ++i) {
        if (scores[i] > max) {
            max = scores[i];
            max_index = i;
        }
    }
    // Returning &scores[max_index] instead of just max lets the caller see
    // *where* the maximum lives, not just its value - useful if the caller
    // wants to modify it in place, or check its position in the array.
    return &scores[max_index];
}
