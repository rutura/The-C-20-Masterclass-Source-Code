module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import concepts_01;
import concepts_02;
import concepts_03;
import concepts_04;
import concepts_05;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void concepts_01_demo(){

	char a_0{ 10 };
	char a_1{ 20 };

	auto result_a = concepts_01::add(a_0, a_1);
	fmt::println("result_a : {}", static_cast<int>(result_a));

	int b_0{ 11 };
	int b_1{ 5 };
	auto result_b = concepts_01::add(b_0, b_1);
	fmt::println("result_b : {}", result_b);


	double c_0{ 11.1 };
	double c_1{ 1.9 };
	auto result_c = concepts_01::add(c_0, c_1);
	fmt::println("result_c : {}", result_c);
}

export void concepts_02_demo(){

	double x{ 6 };
	double y{ 7 };

	//std::string x{"Hello"};
	//std::string y{"World"};

	concepts_02::add(x, y);

	fmt::println("Done!");

}

export void concepts_03_demo(){

	double x{ 67 };
	double y{ 56 };

	// std::string x{"Hello"};
	// std::string y{"World"};

	// auto s = x + y;

	auto result = concepts_03::add(x, y);
	fmt::println("result : {}", result);
	fmt::println("sizeof(result) : {}", sizeof(result));

}


export void concepts_04_demo(){

	int x{ 7 };
	int y{ 5 };

	concepts_04::add(x, y);
}

export void concepts_05_demo(){
	//std::floating_point auto x = concepts_05::add(5,8);
	auto x = concepts_05::add(5, 8);
}