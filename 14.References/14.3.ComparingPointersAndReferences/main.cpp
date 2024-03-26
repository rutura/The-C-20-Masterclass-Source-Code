#include <fmt/format.h>


int main(){

	//Declare pointer and reference

    double double_value {12.34};
    double& ref_double_value {double_value}; // Reference to double_value
    double* p_double_value {&double_value}; //Pointer to double_value
	
	//Reading
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );
	
	//Writting through pointer
	*p_double_value = 15.44;
	
    fmt::println( std::endl;
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );
	
	//Writting through reference
	ref_double_value = 18.44;
	
    fmt::println( std::endl;
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );


    double some_other_double{78.45};

    //Make the reference reference something else.
    ref_double_value = some_other_double;

    fmt::println( "Making the reference reference something else..." );
    fmt::println( std::endl;
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );



    //Make the pointer point to something else
    p_double_value = &some_other_double;
    fmt::println( "Making the pointer point somewhere else..." );
    fmt::println( std::endl;
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
    fmt::println( "&double_value : " << &double_value );
    fmt::println( "&ref_double_value : " << &ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );


    *p_double_value = 555.5;

    fmt::println( std::endl;
	fmt::println( "double_value : " << double_value );
	fmt::println( "ref_double_value : " << ref_double_value );
    fmt::println( "&double_value : " << &double_value );
    fmt::println( "&ref_double_value : " << &ref_double_value );
	fmt::println( "p_double_value : " << p_double_value );
	fmt::println( "*p_double_value : " << *p_double_value );
   
    return 0;
}