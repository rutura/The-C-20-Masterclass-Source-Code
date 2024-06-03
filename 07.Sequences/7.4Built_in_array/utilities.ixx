module;
#include <string_view>
#include <fmt/format.h>
#include <string>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::print("{}\n", msg);
}

export void do_work(){
   // 1. Declaration and Initialization
    // Declare an array of 5 integers
    int arr1[5];

    // Initialize an array of 5 integers with specific values
    int arr2[5] = {1, 2, 3, 4, 5};

    // Partially initialize an array (remaining elements will be zero)
    int arr3[5] = {1, 2};

    // Size of the array is inferred from the initializer list
    int arr4[] = {1, 2, 3, 4, 5};

    // 2. Accessing and Modifying Elements
    // Access and print elements using the subscript operator []
    fmt::println("arr2[0]: {}", arr2[0]);
    fmt::println("arr2[1]: {}", arr2[1]);

    // Modify elements in the array.
    arr2[0] = 10;
    arr2[1] = 20;
    fmt::println("Modified arr2[0]: {}", arr2[0]);
    fmt::println("Modified arr2[1]: {}", arr2[1]);

    // 3. Iterating Over an Array
    // Using a for loop to iterate over the array
    fmt::print("Elements of arr4: ");
    for (int i = 0; i < 5; ++i) {
        fmt::print("{} ", arr4[i]);
    }
    fmt::print("\n");

    // Using a range-based for loop (C++11 and later)
    fmt::print("Elements of arr4 (range-based): ");
    for (const auto& elem : arr4) {
        fmt::print("{} ", elem);
    }
    fmt::print("\n");

    // 4. Multidimensional Arrays
    // Declaring and initializing a 2D array (3x3)
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Accessing and printing elements of a 2D array
    fmt::println("matrix[0][0]: {}", matrix[0][0]);
    fmt::println("matrix[1][1]: {}", matrix[1][1]);
    fmt::println("matrix[2][2]: {}", matrix[2][2]);

    // Iterating over a 2D array
    fmt::print("Elements of matrix: \n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fmt::print("{} ", matrix[i][j]);
        }
        fmt::print("\n");
    }

    // 5. Size of Arrays
    // Getting the size of the array (number of elements)
    int size = sizeof(arr4) / sizeof(arr4[0]);
    fmt::println("Size of arr4: {}", size);

    //Print the size using the std::size function (C++17 and later)
    fmt::println("Size of arr4: {}", std::size(arr4));

}