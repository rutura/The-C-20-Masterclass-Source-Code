module;

#include <string_view>
#include <string>
#include <fmt/format.h>

export module utilities; // Name doesn't have to match the .ixx file

import templates_1;
import templates_2;
import templates_3;
import templates_4;
import templates_5;

//#1: Function template basics
export void templates_1_demo(){

	using templates_1::add;
	using templates_1::Integer;
	using templates_1::Point;

	auto value =add(1,2);
	fmt::print("The value is: {}\n", value);

	Integer a(1);
	Integer b(2);
	auto sum = a + b;
	fmt::print("The sum is: {}\n", sum.get());

	auto result =add(11.1, 22.2);
	fmt::print("The result is: {}\n", result);

	std::string lastname = "Doe";
	std::string firstname = "John";
	auto fullname =add(firstname, lastname);
	fmt::print("The full name is: {}\n", fullname);


	Point p1(1.1, 2.2);
	Point p2(3.3, 4.4);
	auto p3 = p1 + p2;
	fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());

}

//#2: Class template basics 
export void templates_2_demo(){

	using templates_2::Point;
	using templates_1::Integer;	//Everytime we mention Integer in this scope, we mean the Integer class from templates_1

	//Points made up of int
	Point<int> p1(1, 2);
	Point<int> p2(3, 4);
	auto p3 = p1 + p2;
	fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());


	//Points made up of double
	Point<double> p4(1.1, 2.2);
	Point<double> p5(3.3, 4.4);
	auto p6 = p4 + p5;
	fmt::print("The point is: ({}, {})\n", p6.get_x(), p6.get_y());

	//Custom integers
	Point<Integer> p7(Integer(10), Integer(20));
	Point<Integer> p8(Integer(30), Integer(40));
	auto p9 = p7 + p8;
	fmt::print("The point is: ({}, {})\n", p9.get_x().get(), p9.get_y().get());
}

//#3: Template parameter types
export void templates_3_demo(){

	using templates_3::Point;
	using templates_3::maximum;
	using templates_3::add;
	using templates_3::Array;

	//class template
	Point<int> p1(1, 2);
	Point<int> p2(3, 4);
	auto p3 = p1 + p2;
	fmt::print("The point is: ({}, {})\n", p3.get_x(), p3.get_y());

	//function template	
	auto result1 = maximum(11, 2);
	fmt::print("The result is: {}\n", result1);

	//Defaults
	auto result2 = add(11, 2);
	fmt::print("The result is: {}\n", result2);

	//Non-type template parameters
	Array<10> arr1;
	fmt::print("The size is: {}\n", arr1.get_size());
}

//#4: Template template parameters
export void templates_4_demo(){

	using templates_4::Container;
	using templates_4::Processor;
	
	Container<int> container1;
	Processor<Container, int> processor1;
	processor1.process(container1, 1);
	processor1.process(container1, 2);
	processor1.process(container1, 3);

	//We can easily change the container that Processor works with.
	//This is powered by template template parameters.
	Container<std::string> container2; 	
	Processor<Container, std::string> processor2;
	processor2.process(container2, "Hello");
	processor2.process(container2, "World");
}

//#5: Template member functions
export void templates_5_demo(){

	using templates_5::Calculator_1;
	using templates_5::Calculator_2;
	using templates_5::Box;


	//Class is a template, member uses the class template parameter
	Calculator_1<int> calc1; // Calls the default constructor
	auto result1 = calc1.add(1, 2);
	fmt::print("The result is: {}\n", result1);

	Calculator_1<double> calc2; // Calls the default constructor
	auto result2 = calc2.multiply(1.1, 2.2);
	fmt::print("The result is: {}\n", result2);


	//Class is not a template, member is a function template
	Calculator_2 calc3; // Calls the default constructor
	auto result3 = calc3.add(1, 2);
	fmt::print("The result is: {}\n", result3);

	auto result4 = calc3.multiply<double>(1.1, 2.2);
	fmt::print("The result is: {}\n", result4);


	//Both class and member are templates
	Box<int> box1(10);
	auto result5 = box1.compare(10.1);
	auto result6 = box1.compare<int>(10); 	// compare is a template, so we can specify a template argument.
	fmt::print("The result is: {}\n", result5);

	//box1.compare(std::string("10"));	//Error. Can't compare int with string
	//fmt::print("The result is: {}\n", result5);
}



