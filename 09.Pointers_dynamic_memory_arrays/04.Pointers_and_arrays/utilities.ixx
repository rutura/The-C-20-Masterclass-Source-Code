module;
#include <string_view>
#include <fmt/format.h>
#include <iostream>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void pointers_and_arrays(){

	// Pointers and arrays: The relationship
	int scores[10]{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	int *p_score{ scores };

	// Print the address
	fmt::println("scores : {}", fmt::ptr(scores));// Array
	fmt::println("p_score : {}", fmt::ptr(p_score));// Pointer
	fmt::println("&scores[0]  :{} ", fmt::ptr(&scores[0]));

	// Print the content at that address
	fmt::println("Printing out data at array address : ");
	fmt::println("*scores : {}", *scores);
	fmt::println("scores[0] : {}", scores[0]);
	fmt::println("*p_score : {}", *p_score);
	fmt::println("p_score[0] : {}", p_score[0]);


	// Differences
	int number{ 21 };
	p_score = &number;

	// scores = &number; // The array name is a pointer, but a special pointer that kind of identifies
	//  the entire array. You'll get the error  : incompatible types in assignment
	// of 'int*' to 'int[10]'

	fmt::println("p_score : {}", fmt::ptr(p_score));// Pointer

	// std::size() doesn't work for raw pointers
	fmt::println("size : {}", std::size(scores));
	// fmt::println( "size : {}" , std::size(p_score) ); // Compiler error.
} 

export void swap_addresses(){

	int arr0[5]{ 1, 2, 3, 4, 5 };
	int arr1[5]{ 6, 7, 8, 9, 10 };
	int *p_arr1{ arr1 };
	int *p_arr0{ arr0 };

	// Print arr0
	fmt::println("arr0 : ");
	for (size_t i{}; i < std::size(arr0); ++i) {
		 fmt::print("{} ", p_arr0[i]); 
	}
	// Print arr1
	fmt::println("");
	fmt::println("arr1 : ");
	for (size_t i{}; i < std::size(arr1); ++i) {
		fmt::print("{} ", p_arr1[i]);
	}

	// Swapping data the hard way
	/*
	int temp[5];

	//Move data from arr1 into temp
	for (size_t i{ 0 }; i < std::size(arr1); ++i) {
		temp[i] = arr1[i];
	}

	//Move data from arr0 to arr1
	for (size_t i{ 0 }; i < std::size(arr0); ++i) {
		arr1[i] = arr0[i];
	}

	//Move data temp to arr0
	for (size_t i{}; i < std::size(temp); ++i) {
		arr0[i] = temp[i];
	}
	*/

	/*
	int * temp{nullptr};

	temp = arr1;
	arr1 = arr0;
	*/

	int *temp{ nullptr };

	temp = p_arr1;
	p_arr1 = p_arr0;
	p_arr0 = temp;

	// Print arr0
	fmt::println("");
	fmt::println("arr0 : ");
	for (size_t i{}; i < std::size(arr0); ++i) {
		fmt::print("{} ", p_arr0[i]); 
	}

	// Print arr1
	fmt::println("");
	fmt::println("arr1 : ");
	for (size_t i{}; i < std::size(arr1); ++i) {
		fmt::print("{} ", p_arr1[i]); 
	}

}
