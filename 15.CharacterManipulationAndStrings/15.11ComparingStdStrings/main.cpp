#include <fmt/format.h>
#include <string>


int main(){

	std::string hello_str{"Hello"};
    std::string bello_str{"Bello"};
    
	/*
	//Using the comparison operators
	fmt::println( "Comparing with comparison operators : " );
	
    fmt::println( "{} == {} : {}",hello_str,   bello_str ,  (hello_str == bello_str) );//false
    fmt::println( " {} != {} : {}", hello_str,  bello_str , (hello_str != bello_str) ); //true
    fmt::println( "{} > {} : {}", hello_str,   bello_str ,  (hello_str > bello_str) ); // true
    fmt::println(  " {} >= {} : {}" , hello_str, bello_str , (hello_str >= bello_str) ); // true
    fmt::println(  "{} < {} : {}" , hello_str, bello_str , (hello_str < bello_str) ); // false
    fmt::println(  "{} <= {} : {}", hello_str,  bello_str ,  (hello_str <= bello_str) ); // false*/


	//Can even compare std::strings to C-strings
    /*
    const char * c_string1 {"Bello"};
    hello_str = "Hello";
    
    fmt::println( "hello_str.size() : {} ", hello_str.size() );
    fmt::println( "std::strlen(c_string1) : {}" , std::strlen(c_string1) );
    fmt::println(  "{} == {} : (C-String) :{}", hello_str,   c_string1 , (hello_str == c_string1) ); //false
    fmt::println(  "{} (C-String) == {} : {}", c_string1,  hello_str ,  (c_string1 == hello_str) );//false
	fmt::println(   "{} (C-String) >= {} : {}", c_string1,  hello_str ,  (c_string1 >= hello_str) );//false
	fmt::println(  "{} (C-String) < {} : {}", c_string1,   hello_str , (c_string1 < hello_str) ); // true
	*/


	//Be careful about char arrays not terminated with null character
    hello_str = "hello";
	//const char hello_char_array[] {'h','e','l','l','o'}; //The compiler is going to read past the string
														   //until it sees a null character and consider that
														   //end of the string. Your comparisons may give 
														   //erronous results
	
	const char hello_char_array[] {'h','e','l','l','o','\0'};//It works right if you put the '\' yourself
	fmt::println(  "{} == hello_char_array : {}", hello_str,  (hello_str == hello_char_array) );
	
    return 0;
}