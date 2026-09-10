#include <iostream>


inline int age{12};

inline void some_age_function(){
	std::cout << "age : " << age << std::endl;
	std::cout << "&age : " << &age << std::endl;
}

void print_age_2(){
	std::cout << "age(utility2) : " << std::endl;
	some_age_function();
}

static double distance {23.9};

static void some_distance_function(){
	std::cout << "distance : " << distance << std::endl;
	std::cout << "&distance : " << &distance << std::endl;
}


/*
namespace{
	double distance {23.9};

	void some_distance_function(){
		std::cout << "distance : " << distance << std::endl;
		std::cout << "&distance : " << &distance << std::endl;
	}
}
*/
void print_distance_2(){
	std::cout << "distance(utility2) : " << std::endl;
	some_distance_function();
}



