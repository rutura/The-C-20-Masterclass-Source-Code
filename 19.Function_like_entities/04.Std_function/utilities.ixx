module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>
#include <functional>
#include <string>

export module utilities; 

import std_function;
import box_container_it_5;

using iteration_5::BoxContainer;

export void std_function_demo(){

	// Basic usage of std::function : storing function like entities
	// in a unified way.
	std::function<char(const char &)> my_modifier;

	// Function pointer
	my_modifier = std_function::encrypt;
	fmt::println("A encrypted becomes : {}", my_modifier('A'));// D

	// Functor
	std_function::Decrypt decrypt;
	my_modifier = decrypt;
	fmt::println("D decrypted becomes : {}", my_modifier('D'));


	// Lambda function
	my_modifier = [](const char &param) { return static_cast<char>(param + 3); };
	fmt::println("A encrypted becomes : {}", my_modifier('A'));// D

	fmt::println("--------");

	// Storing function like entities in a collection
	fmt::println("Collection of function like entities : ");

	//The functions are not equality comparable, we'll get a compiler error here.
	//But comment out the concept and show that this works. Then revert to the initial state.
	/*
	BoxContainer<std::function<char(const char &)>> func_entities;
	func_entities.add(std_function::encrypt);// Function pointer
	func_entities.add(decrypt);// Functor
	func_entities.add([](const char &param) {// Lambda function
		return static_cast<char>(param + 3);
	});

	for (size_t i{}; i < func_entities.size(); ++i) {
		fmt::println("result {}. D transformed becomes : {}", i, func_entities.get_item(i)('D'));
	}
	*/

	fmt::println("--------");

	// std::function as callback
	fmt::println("Modifying the quote : ");
	BoxContainer<std::string> quote;
	quote.add("The");
	quote.add("sky");
	quote.add("is");
	quote.add("blue");
	quote.add("my");
	quote.add("friend");
	std::cout << "Initial : " << quote << "\n";
	std::cout << "Encrypted : " << std_function::modify(quote, std_function::encrypt) << "\n";
	std::cout << "Decrypted : " << std_function::modify(quote, decrypt) << "\n";


	fmt::println("----------");

	fmt::println("Gettting the best : ");

	auto greater_lexicographically = [](const std::string &str1, const std::string &str2) { return (str1 > str2); };

	fmt::println("larger in size : {}", std_function::get_best(quote, std_function::larger_in_size));
	fmt::println("greater lexicographicaly : {}", std_function::get_best(quote,greater_lexicographically));

}