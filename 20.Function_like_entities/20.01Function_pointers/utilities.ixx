module;
#include <string_view>
#include <vector>
#include <string>
#include <fmt/format.h>

export module utilities; 

import func_pointers;
import callback_functions;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1: Functin pointers
export void function_pointers_demo(){

	//double (*f_ptr) (double, double)  = &func_pointers::add;
	//double(*f_ptr) (double,double) = func_pointers::add;

	//double(*f_ptr) (double,double) {&func_pointers::add};
	//double(*f_ptr) (double,double){func_pointers::add};

	//auto f_ptr = &func_pointers::add;
	//auto f_ptr = func_pointers::add;

	//auto *f_ptr = &func_pointers::add;
	//auto *f_ptr = func_pointers::add;

	//Things gone wroong
	//double (*f_ptr)(double, double) = nullptr;


	//fmt::print("The sum of 3.5 and 4.5 is: {}\n", f_ptr(3.5, 4.5));
}


// #2: Callback functions
export void callback_functions_demo(){

	std::string msg{ "Hello" };
	callback_functions::modify(msg, callback_functions::encrypt);
	fmt::println("outcome : {}", msg);
	fmt::println("------");

	std::vector<std::string> quote;
	quote.push_back("The");
	quote.push_back("sky");
	quote.push_back("is");
	quote.push_back("blue");
	quote.push_back("my");
	quote.push_back("friend");

	//print each string in quote
	for (const auto &str : quote) {
		fmt::println("{}", str);
	}
	fmt::println("------");

	//Encrypt and print
	callback_functions::modify(quote, callback_functions::encrypt);
	//Print each string in encrypted_quote
	for (const auto &str : quote) {
		fmt::println("{}", str);
	}
	fmt::println("------");


	//Decrypt and print
	callback_functions::modify(quote, callback_functions::decrypt);
	//Print each string in decrypted_quote
	for (const auto &str : quote) {
		fmt::println("{}", str);
	}
	fmt::println("-------");

	fmt::println("larger in size : {}", callback_functions::get_best(quote, 
						callback_functions::larger_in_size));
	
	fmt::println("greater lexicographicaly : {}", callback_functions::get_best(quote, 
						callback_functions::greater_lexicographically));

	//Type aliases
	callback_functions::str_comparator callback {callback_functions::larger_in_size};
	fmt::println("larger in size (type alias) : {}", callback_functions::get_best(quote, 
						callback));
}