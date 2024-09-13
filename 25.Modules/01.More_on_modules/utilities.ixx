module;
#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import more_on_modules_01;
import line;
import math;
import math_v1;
import more_on_modules_05;
import more_on_modules_06;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void more_on_modules_01_demo(){
	auto result = more_on_modules_01::add(10, 20);
	fmt::println("result: {}", result);
    more_on_modules_01::greet("John");
    more_on_modules_01::print_name_length("John");
}

export void more_on_modules_02_demo(){
		more_on_modules_02::Point p1{ 1, 2 };	//We can instantiate Point even if the module is not directly imported.
		more_on_modules_02::Point p2{ 3, 4 };
		more_on_modules_02::Line line{ p1, p2 };

		fmt::println("p1 [{}, {}]", p1.x(), p1.y());
		fmt::println("p2 [{}, {}]", p2.x(), p2.y());
}

export void more_on_modules_03_demo(){
	auto result = more_on_modules_03::add(10, 20);
	fmt::println("result : {}", result);

	auto result1 = more_on_modules_03::mult(10, 20);
	fmt::println("result1 : {}", result1);
}


export void more_on_modules_04_demo(){
	auto result1 = more_on_modules_04::add(10, 20);
	fmt::println("result1: {}", result1);

	auto result2 = more_on_modules_04::mult(10, 20);
	fmt::println("result2: {}", result2);
}


export void more_on_modules_05_demo(){
	//Point is not visible. We can't create its instance
    //more_on_modules_05::math::Point p(1, 2);

    //C++ is clever here by creating the p object without explicitly mentioning Point. We have indirect access.
    auto p = more_on_modules_05::generate_random_point();
    //print p
    std::cout << p << std::endl;	//Indirect access to a reachable entity.
    std::cout << "x: " << p.getX() << std::endl;	//Indirect access to a reachable entity.
}

export void more_on_modules_06_demo(){
	// Add 10 to 20 and print the result using the math module
	fmt::println("10 + 20 = {}", more_on_modules_06::add(10, 20));

}