module;
#include <fmt/format.h>

export module utilities;

import time;

export void use_time_demo(){

	it_1::Time24 t1{12, 30};	// Run-time object
	fmt::print("Time: {:02}:{:02}\n", t1.get_hour(), t1.get_minute());
	t1.add_minutes(45);
	fmt::print("Time: {:02}:{:02}\n", t1.get_hour(), t1.get_minute());
	t1.add_hours(2);
	fmt::print("Time: {:02}:{:02}\n", t1.get_hour(), t1.get_minute());

	constexpr it_1::Time24 t2{23, 59}; // Compile-time object
	fmt::print("Time: {:02}:{:02}\n", t2.get_hour(), t2.get_minute());
	//t2.add_minutes(2); // This will not compile. constexpr implies const

	int scores [t2.get_hour()] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	//t3 is from a consteval class
	it_2::Time24 t3{12, 30};	// Run-time object
	//t3.add_minutes(45);	// Error. conseval class can't be used to create run time objects, modifiable objects.

}
