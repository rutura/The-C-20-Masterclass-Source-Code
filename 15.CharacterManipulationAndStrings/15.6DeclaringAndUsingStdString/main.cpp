#include <fmt/format.h>
#include <string>

int main(){


	std::string full_name;//Empty string
    std::string planet {"Earth. Where the sky is blue"};//Initialize with string literal
	std::string prefered_planet{planet};//Initialize with other existing string
    std::string message {"Hello there",5};	//Initialize with part of a string literal.
											//Contains hello
    std::string weird_message(4,'e');//Initialize with multiple copies of a char
									 // contains eeee
    std::string greeting{"Hello World"};
    std::string saying_hello{ greeting,6,5};//Initialize with part of an existing std::string
											// starting at index 6, taking 5 characters.
											//Will contain World.
	
	fmt::println( "full_name : {}" , full_name );
	fmt::println( "planet : {}" , planet );
	fmt::println( "prefered_planet : {}" , prefered_planet );
	fmt::println( "message : {}" , message );
	fmt::println( "weird_message : {}" , weird_message );
	fmt::println( "greeting : {}" , greeting );
	fmt::println( "saying_hello : {}" , saying_hello );

    //Changing std::string at runtime
    planet = "Earth. Where the sky is blue Earth. Where the sky is blue Earth. Where ";
    fmt::println( "planet : {}" , planet );


    //Use a raw array
    const char * planet1 {"Earth. Where the sky is blue Earth."};
    planet1 = "Earth. Where the sky is blue Earth. Where the sky is blue Earth. Where ";
    fmt::println( "planet1 : {}" , planet1 );




   
    return 0;
}