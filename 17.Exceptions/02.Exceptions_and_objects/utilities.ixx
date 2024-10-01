module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import throw_class_objects;
import throw_class_objects_with_inheritance;
import polymorphic_exceptions;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void throw_class_objects_demo(){
	for (size_t i{ 0 }; i < 5; ++i) {

	try {
		throw_class_objects::do_something(i);
		} catch (throw_class_objects::SomethingIsWrong &ex) {
		fmt::println("Exception cought : {}", ex.what());
		}
	}
}

export void throw_class_objects_with_inheritance_demo(){
	for (size_t i{ 0 }; i < 5; ++i) {

		try {
			throw_class_objects_with_inheritance::do_something(i);
		} catch (throw_class_objects_with_inheritance::CriticalError &ex) {
			fmt::println("CriticalError Exception cought : {}", ex.what());
		} catch (throw_class_objects_with_inheritance::SmallError &ex) {
			fmt::println("SmallError Exception cought : {}", ex.what());
		} catch (throw_class_objects_with_inheritance::Warning &ex) {
			fmt::println("Warning Exception cought : {}", ex.what());
		} catch (throw_class_objects_with_inheritance::SomethingIsWrong &ex) {
			fmt::println("SomethingIsWrong Exception cought : {}", ex.what());
		}
	}
}


export void polymorphic_exceptions_demo(){
	for (size_t i{ 0 }; i < 5; ++i) {

		try {
		polymorphic_exceptions::do_something(i);
		}
		/*
		catch(polymorphic_exceptions::CriticalError& ex){
			fmt::println( "CriticalError Exception cought : {}" , ex.what() );
		}
		catch(polymorphic_exceptions::SmallError& ex){
			fmt::println( "SmallError Exception cought : {}" , ex.what() );
		}
		catch(polymorphic_exceptions::Warning& ex){
			fmt::println( "Warning Exception cought : {}" , ex.what() );
		}
		*/
		catch (polymorphic_exceptions::SomethingIsWrong &ex) {
		fmt::println("SomethingIsWrong Exception cought : {}", ex.what());
		}
	}
}