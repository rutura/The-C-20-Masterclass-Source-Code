module;
#include <string_view>
#include <fmt/format.h>
#include <typeinfo>

export module utilities; 

import exceptions_1;
import exceptions_2;
import exceptions_3;
import exceptions_4;
import exceptions_5;


//#1: Rethrowing exceptions
export void exceptions_1_demo(){
	using exceptions_1::SomethingIsWrong;
	using exceptions_1::Warning;
	using exceptions_1::SmallError;
	using exceptions_1::CriticalError;
	using exceptions_1::do_something;

	for (size_t i{ 0 }; i < 5; ++i) {
		try {
			try {
				do_something(i);
			} catch (SomethingIsWrong &ex_inner) {
				if (typeid(ex_inner) == typeid(Warning)) {
					fmt::println(" {}-Inner catch block ,Exception caught: {}", typeid(ex_inner).name(), ex_inner.what());
				} else {
					throw;
					// throw ex_inner; // This will do a copy, and there will be slicing. Beware.
				}
			}
		} catch (SomethingIsWrong &ex_outer) {
			fmt::println(" {}-Outer catch block, Exception caught: {}", typeid(ex_outer).name(), ex_outer.what());
		}
	} // End of for loop

}


//#2: Custom termination
//   . Shown in the main function


//3: Ellipsis catch all block
export void exceptions_3_demo() {
	using exceptions_3::SomethingIsWrong;
	using exceptions_3::Warning;
	using exceptions_3::SmallError;
	using exceptions_3::CriticalError;
	using exceptions_3::some_function;

	try {
		for (size_t i{}; i < 5; ++i) {
			try {
				some_function(i);
			} catch (int ex) {
				fmt::println("int handler - Caught an integer");
			} catch (...) {
				fmt::println("Inner... handler, Caught some exception");
				throw;
			}
		}
	} catch (const std::string &ex) {
		fmt::println("Caught some string exception");
	} catch (...) {
		fmt::println("Outer ...handler caught some other exception");
	}
}

//#4: Noexcept specifier
export void exceptions_4_demo(){
	// Exceptions can't be propagated out of a noexcept function by
	// any means, if you do so the program will terminate, you can
	// also see that the compiler gives you a warning about that.
	/*
	try{
		exceptions_4::some_function();
	}catch(int ex){
		fmt::println( "Catching rethrown exception in main" );
	}
	*/


	// Using noexcept member function
	exceptions_4::Item item;
	try {
		item.do_something_in_class();
	} catch (int ex) {
		fmt::println("main() : Catching exception thrown from method");
	}
}

// #5: Exceptions in destructors
export void exceptions_5_demo(){
	try {
		exceptions_5::Item item;
	} catch (int ex) {
		fmt::println("main() : Catching int exception");
	}

	fmt::println("END.");
}