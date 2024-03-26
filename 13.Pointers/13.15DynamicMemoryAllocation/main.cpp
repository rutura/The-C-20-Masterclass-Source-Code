#include <fmt/format.h>


int main(){

	//How we've used pointers so far
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

   //BAD
	//Writing into uninitialized pointer through dereference
	/*int *p_number2; // Contains junk address : could be anything
    fmt::println( "Writting in the 55" );
	*p_number2 = 55; // Writing into junk address : BAD!
	fmt::println("");
	fmt::println( "Writing into uninitialized pointer through dereference" );
	fmt::println( "p_number2 : {}", p_number2 ); // Reading from junk address.
    fmt::println( "Dereferencing bad memory" );
	fmt::println( "*p_number2 : {}", *p_number2 );*/

	
	//Initializing pointer to null
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
															// BAD, CRASH.
                                                            */


    //Dynamic heap memory
    /*
	int *p_number4{nullptr};
	p_number4 = new int; 	// Dynamically allocate space for a single int on the heap
							// This memory belongs to our program from now on. The system
							// can't use it for anything else, untill we return it.
							//After this line executes, we will have a valid memory location
							// allocated. The size of the allocated memory will be such that it
							// can store the type pointed to by the pointer
						
					
	*p_number4 = 77; // Writting into dynamically allocated memory
	fmt::println( std::endl;
	fmt::println( "Dynamically allocating memory : " );
	fmt::println("*p_number4 : {}", *p_number4 );

    //Return memory to the OS
    delete p_number4;
    p_number4 = nullptr;
    */


    //It is also possible to initialize the pointer with a valid
	//address up on declaration. Not with a nullptr
     int *p_number5{ new int}; // Memory location contains junk value
     int *p_number6{ new int (22) }; // use direct initialization
     int *p_number7{ new int { 23 } }; // use uniform initialization
	 
	fmt::println("");
	 fmt::println( "Initialize with valid memory address at declaration : " );
	 fmt::println( "p_number5 : {}", fmt::ptr(p_number5) );
	 fmt::println( "*p_number5 : {}", *p_number5 ); // Junk value
	 
	 fmt::println( "p_number6 : {}", fmt::ptr(p_number6) );
	 fmt::println( "*p_number6 : {}", *p_number6 );
	 
	 fmt::println( "p_number7 : {}", fmt::ptr(p_number7) );
	 fmt::println( "*p_number7 : {}", *p_number7 );
	 
	 //Remember to release the memory
	  delete p_number5;
	  p_number5 = nullptr;
	  
	  delete p_number6;
	  p_number6 = nullptr;
	  
	  delete p_number7;
	  p_number7 = nullptr;


      //Can reuse pointers
      p_number5 = new int(81);
      fmt::println( "*p_number : {}", *p_number5 );


      delete p_number5;
      p_number5 = nullptr;

      //Calling delete twice on a pointer : BAD!
      p_number5 = new int(99);
      fmt::println( "*p_number5 : {}", *p_number5 );


      delete p_number5;
      delete p_number5;


      //

                                                            
   fmt::println( "Program is ending well" );
    return 0;
}