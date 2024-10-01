module;
#include <string_view>
#include <iostream>
#include <limits>
#include <fmt/format.h>

export module utilities; 

import item;
import point;
import big_item;
//import vector; // GCC doesn't like it when we import vector here. Internal compiler error. This may be fixed in the future.
				 // If you are on a future version of the compiler you may not experience this.
//import number; 	// GCC doesn't like this either.

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void spaceship_op_the_basics(){

	/*std::string m1{"Hello"};
	std::string m2{"World"}; // World comes after Hello in alphabetical order so it's
							// considered to be greater.

	auto result = m1.compare(m2);
	if(result > 0){
		fmt::println( "m1 > m2" );
	}else if(result == 0){
		fmt::println( "m1 == m2" );
	}else{
		fmt::println( "m1 < m2" );
	}*/

	// Three way comparison operator : spaceship operator <=>
	/*int n1{5};
	int n2{5};
	//int n3{0};

	auto result = ( n1 <=> n2);

	fmt::println( "n1 > n2 : {}" , ((n1 <=> n2) > 0) ); // true
	fmt::println( "n1 >= n2 :{} ", ((n1 <=> n2) >= 0) );
	fmt::println( "n1 == n2 : {}" , ((n1 <=> n2) == 0) );
	fmt::println( "n1 < n2 : {}" , ((n1 <=> n2) < 0) );
	fmt::println( "n1 <= n2 : {}" , ((n1 <=> n2) <= 0) );*/


	// Strong ordering
	/*
	int n4{5};
	int n5{5};

	fmt::println( "n4 > n5 : {}" , (n4 > n5) ); // false
	fmt::println( "n4 == n5 : {}" , (n4 == n5) ); //true :  Absolute equality
	fmt::println( "n4 < n5 : {}" , (n4 < n5) ); // false
	*/

	// Weak ordering
	/*std::string m1{"Hello"};
	std::string m2{"HELLO"};

	fmt::println( "m1 > m2 :{} " , (m1 > m2) ); //
	fmt::println( "m1 == m2 :{} " , (m1 == m2) ); // equivalence
	fmt::println( "m1 < m2 :{} " , (m1 < m2) ); //*/

	// Partial ordering
	double d1{ 33.9 };
	double d2{ std::numeric_limits<double>::quiet_NaN() };

	fmt::println("d1 > d2 : {}", (d1 > d2));// false
	fmt::println("d1 == d2 : {}", (d1 == d2));// false
	fmt::println("d1 < d2 : {}", (d1 < d2));// false
}

//#2: Defaulted equality operator
/*
export void defaulted_equality_operator(){
	Item i1{ 1, 2, 3 };
	Item i2{ 1, 2, 33 };

	fmt::println("i1 == i2 : {}", (i1 == i2));
	fmt::println("i1 != i2 : {}", (i1 != i2));
	fmt::println("i1 == 12 : {}", (i1 == 12));
	fmt::println("36 == i2 : {}", (36 == i2));// Watch out : i2==36
	fmt::println("i1 != 12 : {}", (i1 != 12));
	fmt::println("36 != i2 : {}", (36 != i2));
}
*/


export void custom_equality_operator(){

	Point point1(10.0, 10.0);
	Point point2(20.0, 20.0);

	std::cout << "point1: " << point1 << "\n";
	std::cout << "point2: " << point2 << "\n";

	fmt::println("point1 == point2 : {}", (point1 == point2));
	fmt::println("point1 != point2 : {}", (point1 != point2));
	fmt::println("10.5 == point1 : {}", (10.5 == point1));
	fmt::println("point1 == 10.5 : {}", (point1 == 10.5));

}

export void default_ordering_with_spaceship(){

	Item i1{ 1, 2, 5 };
	Item i2{ 1, 2, 4 };

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
	// auto result7 = (i1 > 20);
	// auto result8 = (20 < i1);// ( 20 <=> i1) < 0
	// auto result9 = (i2 != 12);
	// auto result10 = (12 != i2);
}


export void members_without_spaceship(){

	BigItem i1{ 1, 2, 5 };
	BigItem i2{ 1, 2, 4 };


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

export void custom_spaceship_op_for_ordering(){

	// Vector point1(10.0, 10.0);
	// Vector point2(20.0, 20.0);

	// std::cout << "point1: " << point1 << "\n";
	// std::cout << "point2: " << point2 << "\n";

	/*
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
	*/
}

export void logical_operators_simplified(){
	/*
	Number n1(10);
	Number n2(20);


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
	*/
}