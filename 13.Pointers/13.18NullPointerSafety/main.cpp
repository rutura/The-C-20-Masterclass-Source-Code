#include <fmt/format.h>

int main(){

	//Verbose nullptr check
	fmt::println("");
	fmt::println( "Verbose nullptr check: " );
	
    int *p_number{};//Initialized to nullptr
    //p_number = new int(7);
    
    /*
    if(!(p_number==nullptr)){
        fmt::println( "p_number points to a VALID address : {}", p_number );
        fmt::println( "*p_number : {}", *p_number );
    }else{
        fmt::println( "p_number points to an INVALID address." );
    }
    */
    if(p_number){
        fmt::println( "p_number points to a VALID address : {}", fmt::ptr(p_number) );
        fmt::println( "*p_number : {}",*p_number );
    }else{
        fmt::println( "p_number points to an INVALID address." );
    }

    delete p_number;
    nullptr;

    //It is OK call delete on a nullptr
	//Calling delete on a nullptr is OK
    int *p_number1 {};
    
    delete p_number1;	// This won't cause any problem
						//if p_number1 contains nullptr

    // if(p_number1 != nullptr){
    //     delete p_number1;
    // }
   
    return 0;
}