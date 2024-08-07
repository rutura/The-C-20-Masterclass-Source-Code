module;

#include <string_view>
#include <algorithm>
#include <vector>
#include <ranges>
#include <fmt/format.h>

export module utilities; 

import ranges_library_01;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void ranges_library_01_demo(){

	std::vector<int> numbers{ 11, 2, 6, 4, 8, 3, 17, 9 };
	ranges_library_01::print_collection(numbers);

	// std::ranges::all_of()
	fmt::println("");
	fmt::print("std::ranges::all_of(): ");

	auto odd = [](int n) { return n % 2 != 0; };

	auto result = std::ranges::all_of(numbers, odd);

	if (result) {
		fmt::print("All elements in numbers are odd");
	} else {
		fmt::print("Not all elements in numbers are odd");
	}


	// For each
	fmt::println("");
	fmt::print("std::ranges::for_each(): ");
	ranges_library_01::print_collection(numbers);
	std::ranges::for_each(numbers, [](int &n) { n *= 2; });
	ranges_library_01::print_collection(numbers);


	// Sort
	fmt::println("");
	fmt::print("std::ranges::sort(): ");
	ranges_library_01::print_collection(numbers);
	std::ranges::sort(numbers);
	ranges_library_01::print_collection(numbers);


	// Find
	fmt::println("");
	fmt::print("std::ranges::find(): ");
	auto odd_n_position = std::ranges::find_if(numbers, odd);

	if (odd_n_position != std::end(numbers)) {
		fmt::print("numbers contains at least one odd number: {}", *odd_n_position);
	} else {
		fmt::print("numbers does not contain any odd number");
	}


	// Important, copying into outputstream on the fly
	fmt::println("");
	fmt::print("numbers: ");
	fmt::print("{}\n", fmt::join(numbers | std::views::common, " "));
	// std::ranges::copy(numbers,std::ostream_iterator<int>(std::cout, " "));

}