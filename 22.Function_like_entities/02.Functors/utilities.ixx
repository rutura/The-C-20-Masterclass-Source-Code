module;
#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <string>
#include <string_view>

export module utilities;

import functors_01;
import functors_02;
import box_container_it_5;
import functors_03;
import functors_04;

using iteration_5::BoxContainer;

export void functors_01_demo() {
	using functors_01::Encrypt;
	using functors_01::Decrypt;
	using functors_01::encrypt;
	using functors_01::decrypt;
	using functors_01::modify;

	// Modifying through functors
	std::string msg{"Hello world!"};
	Encrypt encryptor;
	Decrypt decryptor;

	fmt::print("Original message: {}\n", msg);
	modify(msg, encryptor);
	fmt::print("Encrypted message: {}\n", msg);
	modify(msg, decryptor);
	fmt::print("Decrypted message: {}\n", msg);

	// Modifying through function pointers
	std::string msg2{"Hello world!"};
	fmt::print("Original message: {}\n", msg2);
	modify(msg2, encrypt);
	fmt::print("Encrypted message: {}\n", msg2);
	modify(msg2, decrypt);
	fmt::print("Decrypted message: {}\n", msg2);
}

export void functors_02_demo() {

	using functors_02::get_best;
	using functors_02::custom_greater;
	using functors_02::Greater;


	std::plus<int> adder;
	std::minus<int> substracter;
	std::greater<int> compare_greater;

	fmt::println("10 + 7: {}", adder(10, 7));            // 17
	fmt::println("10 - 7: {}", substracter(10, 7));       // 3
	fmt::println(" 10 > 7: {}", compare_greater(10, 7));  // true

	fmt::println("---------------------------------");

	BoxContainer<std::string> quote;
	quote.add("The");
	quote.add("sky");
	quote.add("is");
	quote.add("blue");
	quote.add("my");
	quote.add("friend");

	std::greater<std::string> string_comparator{};

	// fmt::println("quote : {}", quote);
	std::cout << "quote: " << quote << "\n";
	//  Built in functor
	fmt::println("greater string : {}", get_best(quote, string_comparator));
	// Custom function pointer
	fmt::println(
		"greater string : {}", get_best(quote, custom_greater<std::string>));
	// Custom functor
	Greater<std::string> greater_string_custom_functor;
	fmt::println("greater string :{} ",get_best(quote, greater_string_custom_functor));

	fmt::println("---------------------------------");

	BoxContainer<int> ints;
	ints.add(10);
	ints.add(3);
	ints.add(6);
	ints.add(72);
	ints.add(23);
	ints.add(4);

	std::greater<int> int_comparator{};
	Greater<int> greater_int_custom_functor;

	std::cout << "ints: " << ints << "\n";
	fmt::println("greater int :{} ", get_best(ints, int_comparator));
	fmt::println("greater int :{} ", get_best(ints, custom_greater<int>));
	fmt::println("greater int :{} ",get_best(ints,greater_int_custom_functor));
	fmt::println("lesser int : {}", get_best(ints,std::less<int>{}));
}


export void functors_03_demo(){

	using functors_03::IsInRange;
	using functors_03::range_sum;

	BoxContainer<double> doubles;
	doubles.add(10.1);
	doubles.add(20.2);
	doubles.add(30.3);
	doubles.add(15);

	std::cout << "doubles: " << doubles << "\n";
	fmt::println("range_sum :{} ", range_sum(doubles, IsInRange<double>(10.0, 15.5))); 
	fmt::println("range_sum :{} ", range_sum(doubles, IsInRange<double>(10.0, 41.5)));


	fmt::println("------");
	//Constraints not satisfied.
	/*
	BoxContainer<std::string> strings;
	strings.add("Hello");
	strings.add("World");
	range_sum(strings,IsInRange<std::string> ("Hello","World"));
	*/

	fmt::println("-----");

	BoxContainer<int> ints;
	ints.add(10);
	ints.add(3);
	ints.add(6);
	ints.add(72);
	ints.add(23);
	ints.add(4);

	std::cout << "ints: " << ints << "\n";
	fmt::println("range_sum :{} ", range_sum(ints, IsInRange<int>(10, 20)));// 10
	fmt::println("range_sum :{} ", range_sum(ints, IsInRange<int>(10, 30)));// 33

}


export void functors_04_demo(){
	functors_04::lambda_sandbox();
}