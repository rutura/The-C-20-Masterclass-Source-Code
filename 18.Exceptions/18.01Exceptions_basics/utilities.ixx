module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import try_catch_blocks;
import need_for_exceptions;
import exceptions_diff_levels;
import multiple_handlers_for_exception;
import nested_try_blocks;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void try_catch_blocks_demo(){
	
	// Showing that that automatic local variables are destroyed when
	// we are thrown out of a try block
	int a{10};
	int b{10};

	try{
		try_catch_blocks::Item item; // When exception is thrown, control immediately exits the try block
					// an automatic local variables are released
					// But pointers may leak memory.
		if( b == 0 )
			throw 110;
		a++; // Just using a and b in here, could use them to do anything.
		b++;
		fmt::println( "Code that executes when things are fine" );
	} catch(int ex){
		fmt::println( "Something went wrong. Exception thrown : {}", ex);
	}
	fmt::println( "Done!" );


	//.Throwing a pointer : recipe for disaster
	// Throwing pointers is a recipe for disaster, as by the time
	// the catch block executes, the memory allocated and used in try
	// block is pointing to invalid data. The program may seem to work
	// sometimes but there are no guarantees you'll always get valid stuff
	// if you dereference pointers allocated in the try block.
	/*
	int c{0};
	try{
		int var{55};
		int* int_ptr = &var;
		if(c == 0)
			throw int_ptr;
		fmt::println( "Keeping doing some other things..." );
	}catch(int* ex){
		fmt::println( "Something went wrong. Exception thrown : ", *ex );
	}
	fmt::println( "END." );
	*/


	// Potential memory leaks
	// The destructor for Item is never called when we're thrown out of the
	// try block, and memory is leaked.
	/*
	int d{0};
	try{
	//try_catch_blocks::Item * item_ptr = new try_catch_blocks::Item();
	std::shared_ptr<try_catch_blocks::Item> item_ptr = std::make_shared<try_catch_blocks::Item>();
	if(d == 0)
		throw 0;
	fmt::println( "Keeping doing some other things..." );
	}catch(int ex){
	fmt::println( "Something went wrong. Exception thrown : {}", ex );
	}
	fmt::println( "END." );
	*/


	// If you throw an exception and it's not handled anywhere in your code,
	// you'll get a hard crash
	/*
	throw 0;
	fmt::println( "Doing something after we throw" );

	fmt::println( "END." );
	*/


	// If copy constructor is either deleted, protected or private, the
	// object can't be thrown as exception. You'll get a compiler error.
	/*

	try {
		try_catch_blocks::MyException e;
		throw e;//

	} catch (try_catch_blocks::MyException ex) {}
	fmt::println("END.");
	*/
}


export void need_for_exceptions_demo(){

	// int division by 0 : CRASH
	const int a{45};
	const int b{0};
	//int result = a/b;		//Some compilers flag division by zero as an error out of the box.
	fmt::println( "Done!" );


	// Downcast using dynamic_cast with references
	// The hierarchy of Animal->Dog has to be polymorphic to be able to do
	// this. This throws an exception because animal has no dog part so the
	// cast won't really work.
	/*
	need_for_exceptions::Animal a;
	need_for_exceptions::Dog& d{dynamic_cast<need_for_exceptions::Dog&>(a)};

	fmt::println( "Done!" );
	*/


	// Exceptions allow us to recover from these errors and give
	// our program a chance to continue running.
	// Integer division
	/*
	const int a{45};
	const int b{0};
	int result;

	try{
		if(b == 0)
		throw 0;
		//result = a/b;	//Some compilers flag division by zero as an error out of the box.
	}
		catch(std::string ex){
		//Some processing
		fmt::println( "Something went wrong : {}", ex );
		}

	catch(int ex){
		fmt::println( "Integer division detected, ex  : {}", ex );
	}

	fmt::println("END." );
	*/


	// Exceptions thrown out of other parts of code written by you
	// or somebody else
	/*
	try {
		need_for_exceptions::process_parameters(10, 0);
	} catch (const char *ex) {
		fmt::println("Exception: {}", ex);
	}

	fmt::println("Done!");
	*/
}


export void exceptions_diff_levels_demo(){

	//exceptions_diff_levels::f1();

	try{
		exceptions_diff_levels::f1();
	}catch(int ex){
		fmt::println( "Handling execution the closest main()" );
	}

	fmt::println("END.");

}

export void multiple_handlers_for_exception_demo(){
	
	try {
		multiple_handlers_for_exception::f1();
	} catch (int ex) {
		fmt::println("Handling execution in main()");
	}
	fmt::println("main() finishing up");
}


export void nested_try_blocks_demo(){
	try {
		nested_try_blocks::some_function();
	} catch (std::string &ex) {
		fmt::println("Main catch block , cought : {}", ex);
	}
	fmt::println("END.");
}