module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import exceptions_1;
import exceptions_2;

//#1: Throwing class objects
export void exceptions_1_demo() {
	for (size_t i{ 0 }; i < 5; ++i) {
		try {
			exceptions_1::do_something(i);
		} catch (exceptions_1::SomethingIsWrong &ex) {
			fmt::println("Exception caught : {}", ex.what());
		}
	}
}


//#2: Throwing class objects with inheritance
export void exceptions_2_demo(){
	using exceptions_2::SomethingIsWrong;
	using exceptions_2::CriticalError;
	using exceptions_2::SmallError;
	using exceptions_2::Warning;
	using exceptions_2::do_something;

	for (size_t i{ 0 }; i < 5; ++i) {
		try {
			do_something(i);
		} catch (CriticalError &ex) {
			fmt::println("CriticalError Exception cought : {}", ex.what());
		} catch (SmallError &ex) {
			fmt::println("SmallError Exception cought : {}", ex.what());
		} catch (Warning &ex) {
			fmt::println("Warning Exception cought : {}", ex.what());
		} catch (SomethingIsWrong &ex) {
			fmt::println("SomethingIsWrong Exception cought : {}", ex.what());
		}
	}
}