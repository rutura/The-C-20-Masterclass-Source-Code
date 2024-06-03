module;
#include <string_view>
#include <fmt/format.h>
#include <array>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::print("{}\n", msg);
}

export void do_work(){
	//1.Declaration and initialization
	/*
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Accessing elements using []
    for (size_t i = 0; i < arr.size(); ++i) {
        fmt::println("arr[{}] = {}", i, arr[i]);
    }
	*/

	//2. Accessing elements using at()
	/*
	    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Accessing elements using at() method
    for (size_t i = 0; i < arr.size(); ++i) {
        fmt::println("arr.at({}) = {}", i, arr.at(i));
    }
	*/

	//3. Modifying elements in the array
	/*
	std::array<int, 5> arr = {1, 2, 3, 4, 5};
    arr[0] = 10;
    arr.at(1) = 20;

    // Printing modified array
    for (size_t i = 0; i < arr.size(); ++i) {
        fmt::println("arr[{}] = {}", i, arr[i]);
    }
	*/

	//4. Using range based for loop
	/*
	std::array<int, 5> arr = {1, 2, 3, 4, 5};

    for (const auto& element : arr) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");
	*/


	//5.Filling an array with a value
	/*
	std::array<int, 5> arr; // Array initialized with junk values

    // Filling array with a single value
    arr.fill(7);

    for (const auto& element : arr) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");
	*/

	//6. Accessing the first and last elements
	/*
	std::array<int, 5> arr = {1, 2, 3, 4, 5};

    fmt::println("First element: {}", arr.front());
    fmt::println("Last element: {}", arr.back());
	*/

	//7. Multi-dimensional: 2D array (3x2)
	/*
    std::array<std::array<int, 2>, 3> arr = {{{1, 2}, {3, 4}, {5, 6}}};

    for (const auto& row : arr) {
        for (const auto& element : row) {
            fmt::print("{} ", element);
        }
        fmt::print("\n");
    }
	*/

	//8. Comparing arrays
	/*
	std::array<int, 3> arr1 = {1, 2, 3};
    std::array<int, 3> arr2 = {1, 2, 3};
    std::array<int, 3> arr3 = {1, 2, 4};
    std::array<int, 3> arr4 = {0, 2, 3};

    // Comparing arrays for equality
    if (arr1 == arr2) {
        fmt::println("arr1 is equal to arr2");
    } else {
        fmt::println("arr1 is not equal to arr2");
    }

    // Comparing arrays for inequality
    if (arr1 != arr3) {
        fmt::println("arr1 is not equal to arr3");
    } else {
        fmt::println("arr1 is equal to arr3");
    }
    // Lexicographical comparison
    if (arr1 < arr3) {
        fmt::println("arr1 is less than arr3");
    } else {
        fmt::println("arr1 is not less than arr3");
    }

    if (arr1 <= arr2) {
        fmt::println("arr1 is less than or equal to arr2");
    } else {
        fmt::println("arr1 is not less than or equal to arr2");
    }

    if (arr3 > arr4) {
        fmt::println("arr3 is greater than arr4");
    } else {
        fmt::println("arr3 is not greater than arr4");
    }

    if (arr3 >= arr1) {
        fmt::println("arr3 is greater than or equal to arr1");
    } else {
        fmt::println("arr3 is not greater than or equal to arr1");
    }
	*/

	//9. Assigning one array to another
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr2 = {6, 7, 8, 9, 10};

    // Printing original arrays
    fmt::println("Original arr1: ");
    for (const auto& element : arr1) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    fmt::println("Original arr2: ");
    for (const auto& element : arr2) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    // Assigning arr2 to arr1
    arr1 = arr2;

    // Printing arrays after assignment
    fmt::println("arr1 after assignment: ");
    for (const auto& element : arr1) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    fmt::println("arr2 after assignment: ");
    for (const auto& element : arr2) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");
	
}