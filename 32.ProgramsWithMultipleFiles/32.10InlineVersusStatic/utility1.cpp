#include <fmt/format.h>

inline int age{12};

inline void some_age_function(){
	fmt::println( "age  : {}" , age );
	fmt::println( "&age : {}" , fmt::ptr(&age ));
}

void print_age_1(){
	fmt::println( "age(utility1) : " );
	some_age_function();
}

static double distance {23.9};

static void some_distance_function(){
	fmt::println( "distance : {}" , distance );
	fmt::println( "&distance : {}" , fmt::ptr(&distance ));
}


/*
namespace{
	double distance {23.9};

	void some_distance_function(){
		fmt::println( "distance : {}" , distance );
		fmt::println( "&distance : {}" , fmt::ptr(&distance ));
	}
}
*/

void print_distance_1(){
	fmt::println( "distance(utility1) : " );
	some_distance_function();
}



