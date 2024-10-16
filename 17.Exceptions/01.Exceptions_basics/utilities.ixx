module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import exceptions_1;
import exceptions_2;
import exceptions_3;
import exceptions_4;
import exceptions_5;

//#1: The basics on ecxeptions in C++
export void exceptions_1_demo(){
	exceptions_1::exceptions_basics();
	exceptions_1::throwing_pointers();
	exceptions_1::potential_memory_leaks();
	exceptions_1::unhandled_exceptions();
	exceptions_1::the_need_for_copy_constructors();
}

//#2: Exploring the need for exceptions
export void exceptions_2_demo(){
	exceptions_2::integer_division_by_zero();
	exceptions_2::downcast_troubles();
	exceptions_2::recover_from_division_by_zero();
	exceptions_2::recover_from_bad_downcast();
	exceptions_2::exceptions_coming_from_elsewhere();
}

//#3: Exploring exceptions from different levels
export void exceptions_3_demo(){
	/*
	//#1: No exception thrown
	exceptions_3::opt_1::f1();

	//#2: Exception thrown from f3() scope : Not handled anywhere
	exceptions_3::opt_2::f1();


	//#3: Exception thrown from f3() scope : Handled in f3()
	exceptions_3::opt_3::f1();

	//#4: Exception thrown from f3() scope : Handled in f2()
	exceptions_3::opt_4::f1();

	//#5: Exception thrown from f3() scope : Handled in f1()
	exceptions_3::opt_5::f1();
	*/

	//#6: Exception thrown from f3() scope : Handled the closest to main
	try{
		exceptions_3::opt_6::f1();
	}catch(int ex){
		fmt::println( "Handling execution the closest main()" );
	}

	//#7: The best thing to do is to handle the exception as close to the source as possible.


	fmt::println("END.");

}

//#4: Multiple handlers for an exception
export void exceptions_4_demo(){
	
	try {
		exceptions_4::f1();
	} catch (int ex) {
		fmt::println("Handling execution in main()");
	}
	fmt::println("main() finishing up");
}


//#5: Nested try blocks
export void exceptions_5_demo(){
	try {
		exceptions_5::some_function();
	} catch (std::string &ex) {
		fmt::println("Main catch block , cought : {}", ex);
	}
	fmt::println("END.");
}