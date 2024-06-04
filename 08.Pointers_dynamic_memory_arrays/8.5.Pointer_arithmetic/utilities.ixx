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

export void p_a_navigation(){
	// Increment/ decrement pointer addresses manually

	int scores[10]{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	// scores++;

	int *p_score{ scores };

	fmt::println("Values in scores array (p_score pointer increment) : ");

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	fmt::println("Address : {},  value : {}", fmt::ptr(p_score), *(p_score));
	++p_score;// Moves froward by sizeof(int) : 4 bytes

	/*
	fmt::println( "Explicit addition of integer : " );
	p_score = scores; // Reset the pointer to the start of the array
	fmt::println( "scores[4] : {}" , *(p_score + 4) ); // Moves forward by 4 * sizeof(int)
	*/

	// Can use loops to print these things out : easier
	/*p_score = scores;

	fmt::println( "Pointer arithmetic on fmt::ptr(p_score)s pointer and a for loop: " );
	for ( size_t i{0} ; i < std::size(scores) ; ++i){
		fmt::println("Value : {}", *(p_score + i) ); // scores[i]
	}*/


	// Can also do arithmetic on the array name
	// just like any pointer.
	/*
	p_score = scores;

	fmt::println( "Pointer arithmetic on array name: " );
	for ( size_t i{0} ; i < std::size(scores) ; ++i){
		fmt::println("Value : {}", *(scores + i) );
		}
		*/

	// Can Print the elements in reverse order
	/*fmt::println( "Elements in reverse order with decrementing pointer arithmetic: " );
	for ( size_t i{std::size(scores)} ; i > 0 ; --i){
		fmt::println("Value : {}", *(scores + i -1) );	// Here we do the -1 thing, because
	}*/

	// Print in reverse order with -- operator on p_score
	/*fmt::println( "Elements in reverse order -- arithmetic on the p_scores pointer: " );
	p_score = scores + std::size(scores) -1;
		for ( size_t i{std::size(scores)} ; i > 0 ; --i){
	}*/

	// Can Print the elements in reverse order with array index
	/*
	fmt::println( "Elements in reverse order with array index notation: " );
	for ( size_t i{std::size(scores)} ; i > 0 ; --i){
		fmt::println("Value : {}", scores [ i -1] );
	}
	*/

	/*
	p_score = scores;

	scores[0] = 31;// Array index notation
	*(scores + 1) = 32;// Equivalent to scores[1] = 32 . Pointer arithmetic on array name
	*(p_score + 2) = 33;// Equivalent to scores[2] = 33 . Pointer arithmetic on p_score pointer

	fmt::println("Printing out the array after modification of 3 first elements: ");
	for (size_t i{ 0 }; i < std::size(scores); ++i) { fmt::println("Value : {}", scores[i]); }
  */
}

export void p_a_distance(){

	int scores[10]{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	// Array index notation
	//     int * pointer1 {&scores[0]};
	//     int * pointer2 {&scores[8]};

	// Pointer arithmetic notation
	int *pointer1{ scores + 0 };
	int *pointer2{ scores + 8 };

	fmt::println("pointer2 - pointer1 : {}", pointer2 - pointer1);// 8
	fmt::println("pointer1 - pointer2 : {}", pointer1 - pointer2);// -8


	std::ptrdiff_t pos_diff = pointer2 - pointer1;
	std::ptrdiff_t neg_diff = pointer1 - pointer2;
	fmt::println("pointer2 - pointer1 : {}", pos_diff);// 8
	fmt::println("pointer1 - pointer2 : {}", neg_diff);// -8
	fmt::println("sizeof(std::ptrdiff_t) : {}", sizeof(std::ptrdiff_t));	
}

export void p_a_compare_pointers(){
	int scores[10]{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	int *pointer1{ &scores[0] };
	int *pointer2{ &scores[8] };

	// Can also compare pointers

	// The further you go in the array, the bigger the address

	fmt::println("Comparing pointers : ");

	fmt::println("pointer1 > pointer2 : {}", (pointer1 > pointer2));
	fmt::println("pointer1 < pointer2 : {}", (pointer1 < pointer2));
	fmt::println("pointer1 >= pointer2 : {}", (pointer1 >= pointer2));
	fmt::println("pointer1 <= pointer2: {}", (pointer1 <= pointer2));
	fmt::println("pointer1 == pointer2 : {}", (pointer1 == pointer2));
	fmt::println("pointer1 != pointer2 : {}", (pointer1 != pointer2));
}

export void p_a_swap_addresses(){

	int arr0[5]{ 1, 2, 3, 4, 5 };
	int arr1[5]{ 6, 7, 8, 9, 10 };

	int *p_arr1{ arr1 };
	int *p_arr0{ arr0 };

	// Print arr0
	fmt::println("arr0 : ");
	for (size_t i{}; i < std::size(arr0); ++i) { fmt::print("{} ", *(p_arr0 + i)); }
	fmt::println("");
	// Print arr1
	fmt::println("arr1 : ");
	for (size_t i{}; i < std::size(arr1); ++i) { fmt::print("{} ", *(p_arr0 + i)); }
	fmt::println("");
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
	fmt::println("arr0 : ");
	for (size_t i{}; i < std::size(arr0); ++i) { fmt::print("{} ", *(p_arr0 + i)); }
	fmt::println("");

	// Print arr1
	fmt::println("arr1 : ");
	for (size_t i{}; i < std::size(arr1); ++i) { fmt::print("{} ", *(p_arr1 + i)); }
	fmt::println("");
}


