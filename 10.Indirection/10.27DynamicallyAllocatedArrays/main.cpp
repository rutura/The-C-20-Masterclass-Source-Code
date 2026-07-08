#include <print>

int main() {

    const size_t size{10};

    // Different ways to declare a dynamic array, and how each initializes.
    double* p_salaries{new double[size]};             // contains garbage values
    int* p_students{new (std::nothrow) int[size]{}};   // every value initialized to 0
    double* p_scores{new (std::nothrow) double[size]{1, 2, 3, 4, 5}}; // first 5 elements
                                                                       // get 1,2,3,4,5;
                                                                       // the rest default to 0

    if (p_scores) {
        std::println("size of scores (it's a regular pointer) : {}", sizeof(p_scores));
        std::println("Successfully allocated memory for scores.");

        // Either array-access notation or pointer arithmetic works here.
        for (size_t i{}; i < size; ++i) {
            std::println("value : {} : {}", p_scores[i], *(p_scores + i));
        }
    }

    delete[] p_salaries;
    p_salaries = nullptr;

    delete[] p_students;
    p_students = nullptr;

    delete[] p_scores;
    p_scores = nullptr;

    // Static arrays vs. dynamic arrays
    std::println("=====================================");

    int scores[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // lives on the stack

    std::println("scores size : {}", std::size(scores));
    for (auto s : scores) {
        std::println("value : {}", s);
    }

    int* p_scores1 = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // lives on the heap
    // std::size() doesn't work on a decayed pointer - the size information
    // is only available on the array itself, not on p_scores1.

    /*
    for (auto s : p_scores1) { // wouldn't compile - p_scores1 is a pointer, not an array
        std::println("value : {}", s);
    }
    */

    delete[] p_scores1; // every array new[] needs a matching delete[]
    p_scores1 = nullptr;

    return 0;
}
