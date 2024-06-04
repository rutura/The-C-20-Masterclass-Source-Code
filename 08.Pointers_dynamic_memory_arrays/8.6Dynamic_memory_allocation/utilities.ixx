module;
#include <string_view>
#include <fmt/format.h>
#include <iostream>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void new_and_delete(){
	// How we've used pointers so far
	/*int number {22}; // Stack

	int * p_number = &number;

	fmt::println("");
	fmt::println( "Declaring pointer and assigning address : " );
	fmt::println( "number : {}", number );
	fmt::println( "p_number : {}", fmt::ptr(p_number) );
	fmt::println( "&number : {}", &number );
	fmt::println( "*p_number : {}", *p_number);


	int * p_number1; // Uninitialized pointer , contains junk address
	int number1 {12};
	p_number1 = &number1; // Make it point to a valid address
	fmt::println("");
	fmt::println( "Uninitialized pointer : " );
	fmt::println( "*p_number1 : {}", *p_number1 );*/

	// BAD
	// Writing into uninitialized pointer through dereference
	/*int *p_number2; // Contains junk address : could be anything
	fmt::println( "Writting in the 55" );
	*p_number2 = 55; // Writing into junk address : BAD!
	fmt::println("");
	fmt::println( "Writing into uninitialized pointer through dereference" );
	fmt::println( "p_number2 : {}", p_number2 ); // Reading from junk address.
	fmt::println( "Dereferencing bad memory" );
	fmt::println( "*p_number2 : {}", *p_number2 );*/


	// Initializing pointer to null
	/*
		//int *p_number3{nullptr}; // Also works
		int * p_number3 {}; // Initialized with pointer equivalent of zero : nullptr
												// A pointer pointing nowhere
	fmt::println( "Writting into nullptr memory" );
		//*p_number3 = 33; // Writting into a pointer pointing nowhere : BAD, CRASH
	fmt::println( "Done writting" );

		fmt::println( std::endl;
		fmt::println( "Reading and writting through nullptr : " );
		//fmt::println( "p_number3 : {}", p_number3 );
		//fmt::println( "*p_number3 : {}", *p_number3 );// Reading from nullptr
																														//
	BAD, CRASH.
															*/


	// Dynamic heap memory
	/*
		int *p_number4{nullptr};
		p_number4 = new int; 	// Dynamically allocate space for a single int on the heap
														// This memory belongs to our program from now on. The system
														// can't use it for anything else, untill we return it.
														//After this line executes, we will have a valid memory location
														// allocated. The size of the allocated memory will be such that
	it
														// can store the type pointed to by the pointer


		*p_number4 = 77; // Writting into dynamically allocated memory
		fmt::println( std::endl;
		fmt::println( "Dynamically allocating memory : " );
		fmt::println("*p_number4 : {}", *p_number4 );

	//Return memory to the OS
	delete p_number4;
	p_number4 = nullptr;
	*/


	// It is also possible to initialize the pointer with a valid
	// address up on declaration. Not with a nullptr
	int *p_number5{ new int };// Memory location contains junk value
	int *p_number6{ new int(22) };// use direct initialization
	int *p_number7{ new int{ 23 } };// use uniform initialization

	fmt::println("");
	fmt::println("Initialize with valid memory address at declaration : ");
	fmt::println("p_number5 : {}", fmt::ptr(p_number5));
	fmt::println("*p_number5 : {}", *p_number5);// Junk value

	fmt::println("p_number6 : {}", fmt::ptr(p_number6));
	fmt::println("*p_number6 : {}", *p_number6);

	fmt::println("p_number7 : {}", fmt::ptr(p_number7));
	fmt::println("*p_number7 : {}", *p_number7);

	// Remember to release the memory
	delete p_number5;
	p_number5 = nullptr;

	delete p_number6;
	p_number6 = nullptr;

	delete p_number7;
	p_number7 = nullptr;


	// Can reuse pointers
	p_number5 = new int(81);
	fmt::println("*p_number : {}", *p_number5);


	delete p_number5;
	p_number5 = nullptr;

	// Calling delete twice on a pointer : BAD!
	p_number5 = new int(99);
	fmt::println("*p_number5 : {}", *p_number5);


	delete p_number5;
	delete p_number5;

	fmt::println("Program is ending well");
}

export void dangling_pointers(){

	// Case1 : Uninitialized pointer
	/*int * p_number; // Dangling uninitialized pointer

	fmt::println("");
	fmt::println( "Case 1 : Uninitialized pointer : ." );
	fmt::println( "p_number : {}", p_number );
	fmt::println( "*p_number : {}" , *p_number ); //CRASH!*/


	// Case 2 : deleted pointer
	/*fmt::println("");
	fmt::println( "Case 2 : Deleted pointer" );
	int * p_number1 {new int{67}};

	fmt::println( "*p_number1 (before delete) : {}", *p_number1 );

	delete p_number1;

	fmt::println( "*p_number1(after delete) : {}", *p_number1 );*/


	// Case 3 : Multiple pointers pointing to same address
	/*fmt::println("");
	fmt::println( "Case 3 : Multiple pointers pointing to same address : " );

	int *p_number3 {new int{83}};
	int *p_number4 {p_number3};

	fmt::println( "p_number3 - {} - {}", p_number3, *p_number3 );
	fmt::println( "p_number4 - {} - {}", p_number4 , *p_number4 );

	//Deleting p_number3
	delete p_number3;

	//p_number4 points to deleted memory. Dereferncing it will lead to
	//undefined behaviour : Crash/ garbage or whatever
	fmt::println( "p_number4(after deleting p_number3) - {} - {}", p_number4 , *p_number4 );*/


	// Solution1 : Initialize your pointers immediately upon declaration
	/*
		fmt::println( std::endl;
		fmt::println( "Solution 1 : " );
	int *p_number5{nullptr};
	int *p_number6{new int(87)};

		//Check for nullptr before use

		if(p_number6!= nullptr){
				fmt::println( "*p_number6 : " << *p_number6 );
		}else{
		fmt::println( "Invalid address" );
	}
	*/


	// Solution 2 :
	// Right after you call delete on a pointer, remember to reset
	// the pointer to nullptr to make it CLEAR it doesn't point anywere
	fmt::println("");
	fmt::println("Solution 2 : ");
	int *p_number7{ new int{ 82 } };

	// Use the pointer however you want
	fmt::println("p_number7 - {} - {}", fmt::ptr(p_number7), *p_number7);

	delete p_number7;
	p_number7 = nullptr;// Reset the pointer

	// Check for nullptr before use
	if (p_number7 != nullptr) {
		fmt::println("*p_number7 : {}", *p_number7);
	} else {
		fmt::println("Invalid memory access!");
	}


	// Solution 3
	// For multiple pointers pointing to the same address ,  Make sure there is
	// one clear pointer (master pointer) that owns the memory ( responsible for releasing when
	// necessary) , other pointers should only be able to dereference when the master pointer is valid

	fmt::println("");
	fmt::println("Solution 3 : ");
	int *p_number8{ new int{ 382 } };// Let's say p_number8 is the master pointer
	int *p_number9{ p_number8 };

	// Dereference the pointers and use them
	fmt::println("p_number8 - {} - {}", fmt::ptr(p_number8), *p_number8);

	if (!(p_number8 == nullptr)) {// Only use slave pointers when master pointer is valid
		fmt::println("p_number9 - {} - {}", fmt::ptr(p_number9), *p_number9);
	}

	delete p_number8;// Master releases the memory
	p_number8 = nullptr;

	if (!(p_number8 == nullptr)) {// Only use slave pointers when master pointer is valid
		fmt::println("p_number9 - {} - {}", fmt::ptr(p_number9), *p_number9);
	} else {
		fmt::println("WARNING : Trying to use an invalid pointer");
	}


	fmt::println("Program is ending well");

}

export void when_new_fails(){

	/*
	//int * data = new int[10000000000000000]; //

	for(size_t i{0} ; i < 10000000 ; ++i){
		int * data = new int[100000000];
	}
	*/

	// exception
	/*
	for(size_t i{0} ; i < 100 ; ++i){
		try{
			int * data = new int[1000000000];
		}catch(std::exception& ex){
			fmt::println( "  Something went wrong : {}", ex.what() );
		}
	}
	*/


	// std::nothrow
	for (size_t i{ 0 }; i < 100; ++i) {

		int *data = new (std::nothrow) int[1000000000];

		if (data != nullptr) {
		fmt::println("Data allocated");
		} else {
		fmt::println("Data allocation failed");
		}
	}


	fmt::println("Program ending well");
}


export void null_ptr_safety(){

	// Verbose nullptr check
	fmt::println("");
	fmt::println("Verbose nullptr check: ");

	int *p_number{};// Initialized to nullptr
	// p_number = new int(7);

	/*
	if(!(p_number==nullptr)){
		fmt::println( "p_number points to a VALID address : {}", p_number );
		fmt::println( "*p_number : {}", *p_number );
	}else{
		fmt::println( "p_number points to an INVALID address." );
	}
	*/
	if (p_number) {
		fmt::println("p_number points to a VALID address : {}", fmt::ptr(p_number));
		fmt::println("*p_number : {}", *p_number);
	} else {
		fmt::println("p_number points to an INVALID address.");
	}

	delete p_number;
	nullptr;

	// It is OK call delete on a nullptr
	// Calling delete on a nullptr is OK
	int *p_number1{};

	delete p_number1;// This won't cause any problem
					// if p_number1 contains nullptr

	// if(p_number1 != nullptr){
	//     delete p_number1;
	// }
}



export void memory_leaks(){

	/*
	int *p_number {new int{67}}; // Points to some address, let's call that address1

	//Should delete and reset here

	int number{55}; // stack variable

	p_number = &number; // Now p_number points to address2 , but address1 is still in use by
						// our program. But our program has lost access to that memory location.
												//Memory has been leaked.
	*/

	// Double allocation
	/*
	int *p_number1 {new int{55}};

		//Use the pointer

		//Should delete and reset here.

	p_number1 = new int{44}; // memory with int{55} leaked.

	delete p_number1;
	p_number1 = nullptr;
	*/

	// Nested scopes with dynamically allocated memory
	{
		int *p_number2{ new int{ 57 } };

		// Use the dynamic memory
	}
	// Memory with int{57} leaked.

	fmt::println("Program ending well");
}





