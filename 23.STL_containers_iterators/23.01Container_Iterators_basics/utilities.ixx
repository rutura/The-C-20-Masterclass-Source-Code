module;

#include <string_view>
#include <vector>
#include <array>
#include <fmt/format.h>

export module utilities; 

import containers_iterators_01;
import containers_iterators_02;
import containers_iterators_03;
import containers_iterators_04;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void containers_iterators_01_demo(){
	containers_iterators_01::use_vector();
	containers_iterators_01::use_array();
}

export void containers_iterators_02_demo(){
	
	std::vector ints1{ 11, 22, 33, 44 };
	std::array ints2{ 100, 200, 300, 400 };

	auto it_begin = ints1.begin();
	auto it_end = ints1.end();

	fmt::println("first elt: {}", *it_begin);
	fmt::println("it == end_it: {}", (it_begin == it_end));

	++it_begin;
	fmt::println("second elt: {}", *it_begin);
	fmt::println("it == end_it: {}", (it_begin == it_end));

	++it_begin;
	fmt::println("third elt: {}", *it_begin);
	fmt::println("it == end_it: {}", (it_begin == it_end));

	++it_begin;
	fmt::println("fourth elt: {}", *it_begin);
	fmt::println("it == end_it: {}", (it_begin == it_end));


	/*
	++it_begin;
	fmt::println("junk elt: {}", *it_begin);
	fmt::println("it == end_it: {}", (it_begin == it_end));// true
	*/


	fmt::println("--------");
	fmt::print("ints1: ");
	containers_iterators_02::print_collection(ints1);

	fmt::print("ints2:");
	containers_iterators_02::print_collection(ints2);

	//Adjust begining and end.
	fmt::println("Adjusting begining and end");
	std::vector ints3{ 11, 22, 33, 44, 55, 66, 77 };
	std::array ints4{ 100, 200, 300, 400, 500, 600 };

	fmt::print("ints3: ");
	containers_iterators_02::print_collection(ints3, 1, 3);
	fmt::print("ints4: ");
	containers_iterators_02::print_collection(ints4, 1, 1);

	//Reverse iterators
	fmt::println("Reverse iterators");
	fmt::print("ints3: ");
	auto rit = ints3.rbegin();
	while (rit != ints3.rend()) {
		fmt::print(" {}", *rit);
		++rit;
	}

}

export void containers_iterators_03_demo(){

	//Constant iterators
	std::vector<int> numbers{ 11, 22, 33, 44, 55, 66, 77 };

	fmt::print("numbers : ");
	containers_iterators_03::print_collection(numbers);

	/*
	std::vector<int>::iterator it = numbers.begin();
	while( it != numbers.end()){
		*it = 100;
		++it;
	}
	*/

	fmt::print("numbers : ");
	containers_iterators_03::print_collection(numbers);

	fmt::println("-------");

	// std::vector<int>::const_iterator c_it = numbers.cbegin();
	auto c_it = numbers.cbegin();
	while (c_it != numbers.end()) {
		// *c_it = 100;
		++c_it;
	}


	// Constant reverse iterators
	auto it1 = numbers.crbegin();
	// std::vector<int>::const_reverse_iterator it1= numbers.crbegin();

	while (it1 != numbers.crend()) {
		//*it1 = 600; // Compiler error, it1 is a const iterator, we can't modify
		// container data through it.
		++it1;
	}

	//std::begin and std::end
	// std::vector<int> vi {1,2,3,4,5,6,7,8,9};
	int vi[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };


	/*
	fmt::print( " Collection : " );
	for(auto it = vi.begin(); it!= vi.end(); ++it){
		fmt::print( "{} ", *it );
	}

	*/

	fmt::println("--------");

	fmt::print(" Collection : ");
	for (auto it = std::begin(vi); it != std::end(vi); ++it) { fmt::print("{} ", *it); }
}


export void containers_iterators_04_demo(){

	//Printing a single referenced value.
	std::vector<int> numbers{ 11, 22, 33, 44, 55, 66, 77 };
	//Works on vectors
	containers_iterators_04::print_referenced_value(numbers.begin() + 2);

	//works on arrays
	std::array<int, 5> arr{ 1, 2, 3, 4, 5 };
	containers_iterators_04::print_referenced_value(arr.begin() + 2);


	//Custom find
	auto result = containers_iterators_04::custom_find(numbers.begin(), numbers.end(), 33);
	if (result != numbers.end()) {
		fmt::println("Found: {}", *result);
	}
	else {
		fmt::println("Not found");
	}

}