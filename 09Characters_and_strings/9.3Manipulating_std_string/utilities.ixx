module;
#include <string_view>
#include <string>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void std_string_declaration(){
	std::string full_name;// Empty string
	std::string planet{ "Earth. Where the sky is blue" };// Initialize with string literal
	std::string prefered_planet{ planet };// Initialize with other existing string
	std::string message{ "Hello there", 5 };// Initialize with part of a string literal.
											// Contains hello
	std::string weird_message(4, 'e');// Initialize with multiple copies of a char
										//  contains eeee
	std::string greeting{ "Hello World" };
	std::string saying_hello{ greeting, 6, 5 };// Initialize with part of an existing std::string
												//  starting at index 6, taking 5 characters.
												// Will contain World.

	fmt::println("full_name: {}", full_name);
	fmt::println("planet: {}", planet);
	fmt::println("prefered_planet: {}", prefered_planet);
	fmt::println("message : {}", message);
	fmt::println("weird_message: {}", weird_message);
	fmt::println("greeting: {}", greeting);
	fmt::println("saying_hello: {}", saying_hello);

	// Changing std::string at runtime
	planet = "Earth. Where the sky is blue Earth. Where the sky is blue Earth. Where ";
	fmt::println("planet: {}", planet);


	// Use a raw array
	const char *planet1{ "Earth. Where the sky is blue Earth." };
	planet1 = "Earth. Where the sky is blue Earth. Where the sky is blue Earth. Where ";
	std::string planet2{ planet1 };
	fmt::println("planet2: {}", planet2);	
}

export void std_string_concatenation(){

	// Concatenating two strings : The + operator
	/*
	fmt::println("");
	fmt::println( "Concatenating two strings : " );

	std::string str1{"Hello"};
	std::string str2{"World"};

	std::string message = str1 + " my " + str2;

	fmt::println( "message : {}", message );
	*/

	// Concatenating string literals : No, No - Compiler Error
	// String literals are expanded into const char* arrays and C++ doesn't know
	// how to add arrays with the + operator. Hence the compiler error.
	/*
	fmt::println("");
	fmt::println( "Concatenating string literals : No,No! Compiler Error " );

	//std::string str3 { "Hello" + "World"}; // Compiler Error
	//std::string str4 = "Hello" + "World";  // Compiler Error
	*/

	// A few ways around string literal concatenation
	/*
	fmt::println("");
	fmt::println( "A few ways around string literal concatenation" );

	std::string str5 {"Hello World"}; 	// Make the string one literal
										//in the first place
	std::string str6 {"Hello" " World"};// Put the literals side by side
										//without the + in between
	std::string str7{std::string{"Hello"} + " World"};//Turn one or both into a std::string
													  //object  and do theconcatenation 
	fmt::println( "str5 : {}",  str5 );
	fmt::println( "str6 : {}",  str6 );
	fmt::println( "str7 : {}", str7);

	using namespace std::string_literals; // necessary for the s suffix
										  // This polutes the namespace.
	std::string str8 {"Hello"s + " World"};// Turn one or both into strings using the
								//s suffix . the string_literals namespace has to be imported
								//for this to work
	fmt::println( "str8 : {}",  str8 );

	//A better way to not polute the namespace
	std::string str9;
	{
			using namespace std::string_literals;
			str9 = "Hello"s + " World";
	}
	fmt::println( "str9 : {}", str9 );
	*/


	// std::string is a compound type, it has properties and behaviors
	// one of the behaviors is append. We access the behaviors using
	// the . operator after the std::string variable name
	/*
	fmt::println("");
	fmt::println( "Using the append method : " );
	std::string str10 {"Hello"};
	std::string str11 {" World"};
	std::string str12 = str10.append(str11);
	fmt::println( "str12 : {}", str12 );

	std::string str13{std::string{"Hello"}.append(" World")};
	fmt::println( "str13 : {}", str13 );
	*/


	// Append can do more than the + operator
	// The + operator is just a convenience for basic concatenation
	/*
	fmt::println("");
	fmt::println( "Append method can do more than + operator : " );
	std::string str14 {"Hello "};
	std::string str15 {str14.append(5,'?')}; // Appends 5 '?' characters
	fmt::println( "str15 : {}", str15 );


	std::string str16{"The world is our shared home."};
	std::string str17{"Hello "};
	std::string str18{str17.append(str16,4,5)};	// Append a sub-section of another string
											  	// starting from index 4 , 5 characters 
	fmt::println( "str18 : {}", str18 );

	//Direct output
	std::string str19{"Hello "};
	fmt::println( "Direct output : {}" , str19.append(str16,4,5) );
	*/


	// Concatenating strings and characters
	/*
	fmt::println("");
	fmt::println( "Concatenating strings and characters : " );
	std::string str20 {"Hello"};
	std::string str21 {"World"};
	std::string str22 {str20 + ' ' + str21};// The space in between is a character
	fmt::println( "str22 : {}",  str22 );

	std::string str23 = "Hello";
	(str23 += ',') += ' ';
	fmt::println( "str23 : {}",  str23 );

	//Another solution
	std::string str24 = "Hello"; // Take out the , and space we added before.
	std::string str25 {"I am here to see you."};
	std::string str26 {str24 + ',' + ' ' + str25};
	fmt::println( "str26 : {}",  str26 );
	*/


	// Appending C-strings and char arrays
	/*
	fmt::println("");
	fmt::println("Appending C-Strings and char arrays : ");
	const char message1[]{ "World" };
	const char *message2{ "World" };

	fmt::println(" + char array : {}", std::string{ "Hello " } + message1);
	fmt::println(" + C-String : {}", std::string{ "Hello " } + message2);
	fmt::println("append char array : {}", std::string{ "Hello " }.append(message1));
	fmt::println("append C-String : {}", std::string{ "Hello " }.append(message2));
	*/

	// Concatenating std::strings and numbers
	std::string str26{ "Hello" };
	//str26 += 67; // Treats 67 as a character code
	str26 += std::to_string(67);// Turn 67 into a string and append it
	//str26 += std::to_string(67.5f);// Treats 67 as a character code
									// When using the += operator, C++ knows to treat the
									// integer operand as a character code and append that to our
									// std::string. But what if we want the 67 appended to std::string
									// literally
	fmt::println("str26 : {}", str26);
}

export void std_string_access_characters(){
	
	//Loop to read characters
	/*
	std::string str1 {"Hello there"};

	//Size of a string : doesn't count the null terminator
	fmt::println( "str1.size() : {}" , str1.size() );

	//Reading characters in std::string : array index operator
	//Regular indexed loop. Can also be adapted to use while and do-while
	//This is left as an exercise.
	fmt::println("");
	fmt::println( "For loop with array index notation : ");

	fmt::println( "str1(for loop) : ") ;
	for(size_t i{}; i < str1.size(); ++i){
		fmt::print( " {}" , str1[i] );
	}
	fmt::println(""); 
	*/

	// Can also use range based for loop
	/*
	std::string str1 {"Hello there"};
	fmt::println("");
	fmt::println( "Using range based for loop : ");

	fmt::println( "str1(range based for loop): ") ;
	for(char value : str1){
		fmt::println("{}" , value);
	}
	fmt::println("");
	*/

	// at() syntax to target characters
	/*
	fmt::println("");
	fmt::println( "Using the std::string::at() method : ");

	std::string str1 {"Hello there"};
	fmt::println( "str1 : (for loop with at()) : ") ;

	for(size_t i{}; i < str1.size(); ++i){
		fmt::print( " {}" , str1.at(i));
	}
	fmt::println("");
	*/

	// Modifying with operator[] and at()
	/*
	std::string str1 {"Hello there"};
	str1[0] = 'B';
	str1.at(1) = 'a';
	fmt::println( "str1(modified) : {}" , str1 );
	*/

	// Getting the front and back characters
	/*
	std::string str2{"The Phoenix King"};
	char& front_char = str2.front();
	char& back_char = str2.back();
	fmt::println( "The front char in str2 is : {}" , front_char );
	fmt::println( "The back char in str2 is : {}" , back_char );

	front_char = 'r';
	back_char = 'd';

	fmt::println( "str2 : {}" , str2 );
	*/


	// c_str method
	//doc : https://en.cppreference.com/w/cpp/string/basic_string/c_str
	//returns const char * to the wrapped string. You shouldn't use
	//it to modify data in the string.
	/*
	std::string str2{"The Phoenix King"};
	const char * wrapped_c_string = str2.c_str();
	fmt::println( "Wrapped c string : {}" , wrapped_c_string );
	//wrapped_c_string[0] = 'e'; // Compiler error
	*/

	// data()
	/*
	std::string str2{ "Hello World" };

	char *data = str2.data();
	fmt::println("Wrapped c string : {}", data);

	data[0] = 'B';// This also changes std::string.

	fmt::println("Wrapped c string (after modification) : {}", data);
	fmt::println("Original string (after modification ) :{}", str2);
	*/
}

export void std_string_size_and_capacity(){

	//Empty, size and length
	std::string str1 {"Hello World"};
	std::string str2;
	std::string str3{};

	//Empty
	fmt::println( "std::string::empty() : " );
	fmt::println( "str1 is empty : {}", str1.empty() );
	fmt::println( "str2 is empty : {}" , str2.empty() );
	fmt::println( "str3 is empty : {}" , str3.empty() );
	fmt::println("");

	//Size
	fmt::println( "std::string::size() : " );
	fmt::println( "str1 contains {} characters" , str1.size() ); //11
	fmt::println( "str2 contains {} characters" , str2.size()  ); // 0
	fmt::println( "str3 contains {} characters" , str3.size()  ); // 0
	fmt::println("");

	//Length
	fmt::println( "std::string::length() : " );
	fmt::println( "str1 contains {} characters" , str1.length()); //11
	fmt::println( "str2 contains {} characters" , str2.length()); // 0
	fmt::println( "str3 contains {} characters" , str3.length()); // 0
	fmt::println("");

	// max_size : max number of characters a string can have on the system
	//Prints : 2147483647 on my system
	/*
	std::string str1 {"Hello World"};
	fmt::println( "std::string can hold {} characters" , str1.max_size());
	*/


	// Capacity
	/*
	std::string str1 {"Hello World"};
	std::string str2;
	fmt::println( "str1 capacity : {}" , str1.capacity() );
	fmt::println( "str2 capacity : {}" , str2.capacity() );

	str1 = "The sky is so blue, the grass is green. Kids are running all over the place";

	fmt::println( "str1 size : {}" , str1.size() );
	fmt::println( "str1 capacity : {}" , str1.capacity() );
	*/

	// Reserve : Update the capacity
	/*
	std::string str1 {"Hello World"};
	fmt::println( "str1 capacity : {}" , str1.capacity() ); // 15
	fmt::println( "str1 size : {}" , str1.size() );

	str1.reserve(100);

	fmt::println( "str1 after reserve : {}" , str1 );
	fmt::println( "str1 capacity : {}" , str1.capacity() ); // 100
	fmt::println( "str1 size : {}" , str1.size() );
	*/


	// shrink_to_fit
	/*
	std::string str1{ "Hello World" };// 11
	str1.reserve(100);

	fmt::println("str1 capacity : {}", str1.capacity());// 100
	fmt::println("str1 size : {}", str1.size());// 11

	str1.shrink_to_fit();

	fmt::println("str1 capacity : {}", str1.capacity());// 11
	fmt::println("str1 size : {}", str1.size());// 11
	*/

}

export void std_string_modify(){

	// Clear : Removes all characters from the string.
	std::string str1 {"The Lion Dad"};

	fmt::println( "str1 is : {}" , str1 );
	fmt::println( "str1 size : {}" , str1.size() );
	fmt::println( "str1 capacity : {}" , str1.capacity() );

	str1.clear();

	fmt::println( "str1 is : {}" , str1 );
	fmt::println( "str1 size : {}" , str1.size() );
	fmt::println( "str1 capacity : {}" , str1.capacity());

	// Insert (1)
	//(1)basic_string& insert( size_type index, size_type count, CharT ch );
	// Inserts count characters in the string starting at index index
	/*
	std::string str2 {"122"};
	fmt::println( "str2 : {}" , str2 );

	str2.insert(1,4,'3');//Insert 4 instances of the '3' character starting at index 1 in str2.

	fmt::println( "str2 : {}" , str2 );//1322
	*/

	// Insert (2)
	//(2)basic_string& insert( size_type index, const CharT* s );
	// Inserts null-terminated character string pointed to by s
	// at the position index. The length of the string is determined
	// by the first null character.
	/*
	std::string str3 {"Hello!"};
	const char * txt3{" World"};

	fmt::println( "str3 : {}" , str3 );//Hello

	str3.insert(5,txt3);

	fmt::println( "str3 : {}" , str3 );//Hello World!
	*/


	// Insert (3)
	//(3)basic_string& insert( size_type index, const CharT* s, size_type count );
	// Inserts the characters in the range [s, s+count) at the position index.
	// The range can contain null characters.
	/*
	std::string str4{"Hello!"};
	const char * txt4{" World Health Organization"};

	fmt::println( "str4 : {}" , str4 );

	str4.insert(5,txt4,6);

	fmt::println( "str4 : {}" , str4 );
	*/


	// Insert (4)
	//(4)basic_string& insert( size_type index, const basic_string& str );
	// Inserts string str at the position index
	/*
	std::string str5{" World"};
	std::string str6{"Hello!"};

	fmt::println( "str6 : {}" , str6 );

	str6.insert(5,str5);

	fmt::println( "str6 : {}" , str6 );
	*/


	// Insert (5)
	/*
	//(5)basic_string& insert( size_type index, const basic_string& str,
	//                  size_type index_str, size_type count = npos);
	// Inserts a string, obtained by str.substr(index_str, count) at the position index
	std::string str7{"Hello!"};
	std::string str8{"Statistical Analysis of the World Population."};

	fmt::println( "str7 : {}" , str7 );

	str7.insert(5,str8,27,6);

	fmt::println( "str7 : {}" , str7 );	//Hello World!
	*/


	// Erase
	// basic_string& erase( size_type index = 0, size_type count = npos );
	// Starting at index index, erase count characters from the string
	// Notice that this function returns a referennce
	/*
	std::string str9 {"Hello World is a message used to kick things of when learning programming!"};;

	str9.erase(11,str9.size() - 12);
	fmt::println( "str9 : {}" , str9 );

	//Reset str9.
	str9 = "Hello World is a message used kick things off when learning programming!";

	//Direct print out.Because this method returns a reference to the modified string
	fmt::println( "str9 : {}" , str9.erase(11,str9.size() - 12));
	*/


	// push_back
	/*
	// void push_back( CharT ch );
	// Appends the given character ch to the end of the string.
	std::string str10{ "Hello World" };
	str10.push_back('!');
	fmt::println("str10 : {}", str10);


	// pop_back
	// void pop_back();
	// Removes the last character from the string.
	std::string str11{ "Hello World!!" };
	str11.pop_back();
	fmt::println("str11 : {}", str11);
	*/
}



