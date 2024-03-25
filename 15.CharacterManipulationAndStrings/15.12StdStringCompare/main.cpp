#include <fmt/format.h>
#include <string>


int main(){


	//Compare (1)
    //int compare( const basic_string& str ) const noexcept;(1)
	//Compares this string to str.
	/*
	std::string str1{"Hello"};
    std::string str2{"World"};
	
    fmt::println( "str1 : {}" , str1 );
	fmt::println( "str2 : {}" , str2 );
    fmt::println( "str1.compare(str2) : {}" , str1.compare(str2) ); // negative
    fmt::println( "str2.compare(str1) : {}" , str2.compare(str1) ); // positive
    */

	//Compare (2)
    //int compare( size_type pos1, size_type count1,const basic_string& str ) const; (2)
	//Compares a  substring  of this string(from pos1, going count1 positions) to str
	/*
	std::string str1 = "Hello";
    std::string str3{"Hello World"};
    fmt::println( "Comparing 'World' to 'Hello' : {}" , str3.compare(6,5,str1) );//1
    */

	//Compare (3)
    //int compare( const CharT* s ) const;(4)
	//Compares this string to the null-terminated character sequence beginning 
    //at the character pointed to by s.
    std::string str5{"Hello"};
    const char* message {"World"};
    fmt::println( "Comparing Hello to World : {}" , str5.compare(message) );//-1
    fmt::println( "Comparing Hello to World : {}" , str5.compare("World") ); //-1


    return 0;
}