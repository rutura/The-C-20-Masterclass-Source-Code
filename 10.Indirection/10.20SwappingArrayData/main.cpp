#include <print>

int main() {

    int arr0[5]{1, 2, 3, 4, 5};
    int arr1[5]{6, 7, 8, 9, 10};
    int* p_arr1{arr1};
    int* p_arr0{arr0};

    std::print("arr0 : ");
    for (size_t i{}; i < std::size(arr0); ++i) {
        std::print("{} ", p_arr0[i]);
    }
    std::println("");

    std::print("arr1 : ");
    for (size_t i{}; i < std::size(arr1); ++i) {
        std::print("{} ", p_arr1[i]);
    }
    std::println("");

    // Swapping data the hard way: copy every element through a temporary array.
    /*
    int temp[5];

    for (size_t i{0}; i < std::size(arr1); ++i) {
        temp[i] = arr1[i];
    }
    for (size_t i{0}; i < std::size(arr0); ++i) {
        arr1[i] = arr0[i];
    }
    for (size_t i{}; i < std::size(temp); ++i) {
        arr0[i] = temp[i];
    }
    */

    // Swapping the array names directly doesn't work - an array name isn't
    // a reassignable pointer variable (see 11.7PointersAndArrays).
    /*
    int* temp{nullptr};
    temp = arr1;
    arr1 = arr0; // compiler error
    */

    // Swapping what the pointers point to, instead of the data itself, is
    // just three pointer assignments - no element-by-element copying needed.
    int* temp{nullptr};

    temp = p_arr1;
    p_arr1 = p_arr0;
    p_arr0 = temp;

    std::print("arr0 : ");
    for (size_t i{}; i < std::size(arr0); ++i) {
        std::print("{} ", p_arr0[i]);
    }
    std::println("");

    std::print("arr1 : ");
    for (size_t i{}; i < std::size(arr1); ++i) {
        std::print("{} ", p_arr1[i]);
    }
    std::println("");

    // Same swap again, written with pointer-arithmetic dereferencing
    // (*(p + i)) instead of array-index notation (p[i]) - both are
    // equivalent, array notation is just easier to read.
    std::println("");
    std::println("Same swap, with pointer-arithmetic dereferencing : ");

    p_arr0 = arr0;
    p_arr1 = arr1;

    std::print("arr0 : ");
    for (size_t i{}; i < std::size(arr0); ++i) {
        std::print("{} ", *(p_arr0 + i));
    }
    std::println("");

    std::print("arr1 : ");
    for (size_t i{}; i < std::size(arr1); ++i) {
        std::print("{} ", *(p_arr1 + i));
    }
    std::println("");

    temp = p_arr1;
    p_arr1 = p_arr0;
    p_arr0 = temp;

    std::print("arr0 : ");
    for (size_t i{}; i < std::size(arr0); ++i) {
        std::print("{} ", *(p_arr0 + i));
    }
    std::println("");

    std::print("arr1 : ");
    for (size_t i{}; i < std::size(arr1); ++i) {
        std::print("{} ", *(p_arr1 + i));
    }
    std::println("");

    return 0;
}
