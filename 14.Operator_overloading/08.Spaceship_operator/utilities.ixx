module;
#include <string_view>
#include <iostream>
#include <limits>
#include <fmt/format.h>

export module utilities; 

import spaceship_ops_1;
import spaceship_ops_2;
import spaceship_ops_3;
import spaceship_ops_4;
import spaceship_ops_5;
import spaceship_ops_6;
import spaceship_ops_7;

//import vector; // GCC doesn't like it when we import vector here. Internal compiler error. This may be fixed in the future.
				 // If you are on a future version of the compiler you may not experience this.
//import number; 	// GCC doesn't like this either.

//#1: The basics
export void spaceship_ops_1_demo(){
	spaceship_ops_1::spaceship_op_the_basics();

}

//#2: Defaulted equality operator
export void spaceship_ops_2_demo(){
	spaceship_ops_2::Item i1{ 1, 2, 3 };
	spaceship_ops_2::Item i2{ 1, 2, 33 };

	fmt::println("i1 == i2 : {}", (i1 == i2));
	fmt::println("i1 != i2 : {}", (i1 != i2));
	fmt::println("i1 == 12 : {}", (i1 == 12));
	fmt::println("36 == i2 : {}", (36 == i2));// Watch out : i2==36
	fmt::println("i1 != 12 : {}", (i1 != 12));
	fmt::println("36 != i2 : {}", (36 != i2));

}

//#3: Custom equality operator
export void spaceship_ops_3_demo(){
	spaceship_ops_3::Point point1(10.0, 10.0);
	spaceship_ops_3::Point point2(20.0, 20.0);

	std::cout << "point1: " << point1 << "\n";
	std::cout << "point2: " << point2 << "\n";

	fmt::println("point1 == point2 : {}", (point1 == point2));
	fmt::println("point1 != point2 : {}", (point1 != point2));
	fmt::println("10.5 == point1 : {}", (10.5 == point1));
	fmt::println("point1 == 10.5 : {}", (point1 == 10.5));

}

//#4: Default ordering with spaceship
export void spaceship_ops_4_demo(){

	spaceship_ops_4::Item i1{ 1, 2, 5 };
	spaceship_ops_4::Item i2{ 1, 2, 4 };

	//auto result1 = (i1 > i2);
	auto result1 = ( (i1 <=> i2) > 0); // A possible option for the compiler magic
	fmt::println(" i1 > i2 : {}" , result1 );

	//auto result2 = (i1 >= i2);
	auto result2 = ( (i1 <=> i2) >= 0); // A possible option for the compiler magic
	fmt::println(" i1 >= i2 : {}" , result2 );

	auto result3 = (i1 == i2);
	fmt::println(" i1 == i2 : {}" , result3 );

	auto result4 = (i1 != i2);
	fmt::println(" i1 != i2 : {}" , result4 );

	//auto result5 = (i1 < i2);
	auto result5 = ( (i1 <=> i2) < 0); // A possible option for the compiler magic
	fmt::println(" i1 < i2 : {}" , result5 );

	//auto result6 = (i1 <= i2);
	auto result6 = ( (i1 <=> i2) <= 0); // A possible option for the compiler magic
	fmt::println(" i1 <= i2 : {}" , result6 );


	// Implicit conversions
	auto result7 = (i1 > 20);
	auto result8 = (20 < i1);// ( 20 <=> i1) < 0
	auto result9 = (i2 != 12);
	auto result10 = (12 != i2);
}


//#5: Members without spaceship
export void spaceship_ops_5_demo(){

	spaceship_ops_5::BigItem i1{ 1, 2, 5 };
	spaceship_ops_5::BigItem i2{ 1, 2, 4 };


	// auto result1 = (i1 > i2);
	auto result1 = ((i1 <=> i2) > 0);// A possible option for the compiler magic
	fmt::println(" i1 > i2: {}", result1);

	// auto result2 = (i1 >= i2);
	auto result2 = ((i1 <=> i2) >= 0);// A possible option for the compiler magic
	fmt::println(" i1 >= i2: {}", result2);

	auto result3 = (i1 == i2);
	fmt::println(" i1 == i2: {}", result3);

	auto result4 = (i1 != i2);
	fmt::println(" i1 != i2: {}", result4);

	// auto result5 = (i1 < i2);
	auto result5 = ((i1 <=> i2) < 0);// A possible option for the compiler magic
	fmt::println(" i1 < i2: {}", result5);

	// auto result6 = (i1 <= i2);
	auto result6 = ((i1 <=> i2) <= 0);// A possible option for the compiler magic
	fmt::println(" i1 <= i2: {}", result6);


	// Implicit conversions
	auto result7 = (i1 > 20);
	auto result8 = (20 < i1);// ( 20 <=> i1) < 0
	auto result9 = (i2 != 12);
	auto result10 = (12 != i2);
}

//#6: Custom spaceship operator for ordering
export void spaceship_ops_6_demo(){

	spaceship_ops_6::Vector point1(10.0, 10.0);
	spaceship_ops_6::Vector point2(20.0, 20.0);

	std::cout << "point1: " << point1 << "\n";
	std::cout << "point2: " << point2 << "\n";

	auto result1 = (point1 > point2);
	fmt::println("point1 > point2 : {}", result1);

	auto result2 = (point1 >= point2);
	fmt::println("point1 >= point2 : {}", result2);

	auto result3 = (point1 == point2);
	fmt::println("point1 == point2 : {}", result3);

	auto result4 = (point1 != point2);
	fmt::println("point1 != point2 : {}", result4);

	auto result5 = (point1 < point2);
	fmt::println("point1 < point2 : {}", result5);

	auto result6 = (point1 <= point2);
	fmt::println("point1 <= point2 : {}", result6);


	// Implicit conversions
	fmt::println("point1 > 20.1 : {}", (point1 > 20.1));
	// fmt::println( "20.1 > point1 : {}" , (20.1 > point1) );
	fmt::println("20.1 > point1 : {}", ((point1 <=> 20.1) < 0));
	//((point1 <=> 20.1) < 0)
}

//#7: Logical operators simplified
export void spaceship_ops_7_demo(){
	spaceship_ops_7::Number n1(10);
	spaceship_ops_7::Number n2(20);


	fmt::println("n1 > n2 : {}", (n1 > n2));
	fmt::println("15 > n2 : {}", (15 > n2));
	fmt::println("n1 > 25 : {}", (n1 > 25));

	fmt::println("n1 >= n2 : {}", (n1 >= n2));
	fmt::println("15 >= n2 : {}", (15 >= n2));
	fmt::println("n1 >= 25 : {}", (n1 >= 25));

	fmt::println("n1 == n2 : {}", (n1 == n2));
	fmt::println("15 == n2 : {}", (15 == n2));
	fmt::println("n1 == 25 : {}", (n1 == 25));

	fmt::println("n1 < n2 : {}", (n1 < n2));
	fmt::println("15 < n2 : {}", (15 < n2));
	fmt::println("n1 < 25 : {}", (n1 < 25));

	fmt::println("n1 <= n2 : {}", (n1 <= n2));
	fmt::println("15 <= n2 : {}", (15 <= n2));
	fmt::println("n1 <= 25 : {}", (n1 <= 25));
}