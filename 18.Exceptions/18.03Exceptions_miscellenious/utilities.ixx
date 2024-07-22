module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import rethrowing_exceptions;
import ellipsis_catch_all;
import noexcept_specifier;
import exceptions_in_destructors;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void rethrowing_exceptions_demo(){

	for (size_t i{ 0 }; i < 5; ++i) {
		try {
		try {
			rethrowing_exceptions::do_something(i);
		} catch (rethrowing_exceptions::SomethingIsWrong &ex_inner) {
			if (typeid(ex_inner) == typeid(rethrowing_exceptions::Warning)) {
			fmt::println(" {}-Inner catch block ,Exception cought: {}", typeid(ex_inner).name(), ex_inner.what());
			} else {
			throw;//
			// throw ex_inner;//This will do a copy, and there will be slicing.Beware.
			}
		}
		} catch (rethrowing_exceptions::SomethingIsWrong &ex_outer) {
			fmt::println(" {}-Outer catch block, Exception cought: {}", typeid(ex_outer).name(), ex_outer.what());
		}
	}// End of for loop

}


export void ellipsis_catch_all_demo(){
	try {
		for (size_t i{}; i < 5; ++i) {
		try {
			ellipsis_catch_all::some_function(i);
		} catch (int ex) {
			fmt::println("int handler- Cought an integer");
		} catch (...) {
			fmt::println("Inner... handler , Cought some exception");
			throw;
		}
		}
	} catch (const std::string &ex) {
		fmt::println("Cought some string exception");
	} catch (...) {
		fmt::println("Outer ...handler cought some other exception");
	}
}

export void noexcept_specifier_demo(){
	// Exceptions can't be propagated out of a noexcept function by
	// any means, if you do so the program will terminate, you can
	// also see that the compiler gives you a warning about that.
	try{
		noexcept_specifier::some_function();
	}catch(int ex){
		fmt::println( "Catching rethrown exception in main" );
	}


	// Using noexcept member function
	/*
	noexcept_specifier::Item item;
	try {
		item.do_something_in_class();
	} catch (int ex) {
		fmt::println("main() : Catching exception thrown from method");
	}
	*/
}

export void exceptions_in_destructors_demo(){
	try {
		exceptions_in_destructors::Item item;
	} catch (int ex) {
		fmt::println("main() : Catching int exception");
	}

	fmt::println("END.");
}