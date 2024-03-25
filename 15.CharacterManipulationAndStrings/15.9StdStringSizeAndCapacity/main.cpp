#include <fmt/format.h>
#include <string>


int main(){

    /*std::string str1 {"Hello World"};
    std::string str2;
    std::string str3{};
    
    //Empty
    fmt::println( "std::string::empty() : " );
    fmt::println( "str1 is empty : {}", str1.empty() );
    fmt::println( "str2 is empty : {}" , str2.empty() );
    fmt::println( "str3 is empty : {}" , str3.empty() );

    //Size
    fmt::println( "std::string::size() : " );
    fmt::println( "str1 contains {} characters" , str1.size() ); //11
    fmt::println( "str2 contains {} characters" , str2.size()  ); // 0
    fmt::println( "str3 contains {} characters" , str3.size()  ); // 0

   //Length
    fmt::println( "std::string::length() : " );
    fmt::println( "str1 contains {} characters" , str1.length()); //11
    fmt::println( "str2 contains {} characters" , str2.length()); // 0
    fmt::println( "str3 contains {} characters" , str3.length()); // 0*/

    //max_size : max number of characters a string can have on the system
    /*
	//Prints : 2147483647 on my system
    std::string str1 {"Hello World"};
    fmt::println( "std::string can hold {} characters" , str1.max_size());
    */


    //Capacity
    /*std::string str1 {"Hello World"};
    std::string str2;
    fmt::println( "str1 capacity : {}" , str1.capacity() );
	fmt::println( "str2 capacity : {}" , str2.capacity() );
	
	str1 = "The sky is so blue, the grass is green. Kids are running all over the place";
	
    fmt::println( "str1 size : {}" , str1.size() );
	fmt::println( "str1 capacity : {}" , str1.capacity() );*/

    //Reserve : Update the capacity
    /*
    std::string str1 {"Hello World"};
	fmt::println( "str1 capacity : {}" , str1.capacity() ); // 15
	fmt::println( "str1 size : {}" , str1.size() );

    str1.reserve(100);
    
    fmt::println( "str1 after reserve : {}" , str1 );
	fmt::println( "str1 capacity : {}" , str1.capacity() ); // 100
	fmt::println( "str1 size : {}" , str1.size() );
	*/


    //shrink_to_fit
    std::string str1 {"Hello World"}; // 11
    str1.reserve(100);

	fmt::println( "str1 capacity : {}" , str1.capacity() ); //100
	fmt::println( "str1 size : {}" , str1.size() ); // 11

	str1.shrink_to_fit();
 
	fmt::println( "str1 capacity : {}" , str1.capacity() ); //11
	fmt::println( "str1 size : {}" , str1.size() );//11

    return 0;
}