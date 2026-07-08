#include <print>

// Declarations
double sum(const double array[][3], size_t size);
double sum_3d(const double array[][3][2], size_t size);

int main() {

    double weights[][3]{
        {10.0, 20.0, 30.0},
        {40.0, 50.0, 60.0},
        {70.0, 80.0, 90.0},
        {100.0, 110.0, 120.0}};
    double weights_3d[][3][2]{
        {
            {10, 20},
            {30, 40},
            {50, 60},
        },
        {
            {70, 80},
            {90, 100},
            {110, 120},
        }};

    double result = sum(weights, std::size(weights));
    std::println("2d array sum : {}", result);

    result = sum_3d(weights_3d, std::size(weights_3d));
    std::println("3d array sum : {}", result);

    return 0;
}

// Function definitions
double sum(const double array[][3], size_t size) {
    double sum{};
    for (size_t i{}; i < size; ++i) {   // loop through rows
        for (size_t j{}; j < 3; ++j) {  // loop through elements in a row
            sum += array[i][j]; // array-access notation
            // sum += *(*(array + i) + j); // equivalent pointer arithmetic -
            // confusing; prefer array notation
        }
    }
    return sum;
}

double sum_3d(const double array[][3][2], size_t size) {
    double sum{};
    for (size_t i{}; i < size; ++i) {
        for (size_t j{}; j < 3; ++j) {
            for (size_t k{}; k < 2; ++k) {
                sum += array[i][j][k];
                // sum += *(*(*(array + i) + j) + k);
            }
        }
    }
    return sum;
}
