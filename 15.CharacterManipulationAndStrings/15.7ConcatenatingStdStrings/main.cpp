#include <iostream>
#include <string>

int main(){

	//Concatenating two strings : The + operator
    /*
	std::cout << std::endl;
	std::cout << "Concatenating two strings : " << std::endl;

	std::string str1{"Hello"};
	std::string str2{"World"};

	std::string message = str1 + " my " + str2;
        
	std::cout << "message : " << message << std::endl;
    */

	//Concatenating string literals : No, No - Compiler Error
	//String literals are expanded into const char* arrays and C++ doesn't know
	//how to add arrays with the + operator. Hence the compiler error.
    /*
	std::cout << std::endl;
	std::cout << "Concatenating string literals : No,No! Compiler Error " << std::endl;
	
	//std::string str3 { "Hello" + "World"}; // Compiler Error
	//std::string str4 = "Hello" + "World";  // Compiler Error
    */

	//A few ways around string literal concatenation
    /*
	std::cout << std::endl;
	std::cout << "A few ways around string literal concatenation" << std::endl;
            
	std::string str5 {"Hello World"}; 	// Make the string one literal
										//in the first place
	std::string str6 {"Hello" " World"};// Put the literals side by side
										//without the + in between
	std::string str7{std::string{"Hello"} + " World"};//Turn one or both into a std::string
													 //object  and do the concatenation
	std::cout << "str5 : " << str5 << std::endl;
	std::cout << "str6 : " << str6 << std::endl;
	std::cout << "str7 : " << str7 << std::endl;
                                                     
	using namespace std::string_literals; // necessary for the s suffix
										  // This polutes the namespace in main
	std::string str8 {"Hello"s + " World"};// Turn one or both into strings using the 
                                    //s suffix . the string_literals namespace has to be imported
                                    //for this to work
	std::cout << "str8 : " << str8 << std::endl;
									
	//A better way to not polute the namespace
	std::string str9;
	{
		using namespace std::string_literals;
		str9 = "Hello"s + " World";
	}
	std::cout << "str9 : " << str9 << std::endl;
    */


	//std::string is a compound type, it has properties and behaviors
	//one of the behaviors is append. We access the behaviors using
	//the . operator after the std::string variable name
    /*
	std::cout << std::endl;
	std::cout << "Using the append method : " << std::endl;
	std::string str10 {"Hello"};
	std::string str11 {" World"};
	std::string str12 = str10.append(str11);
	std::cout << "str12 : " << str12 << std::endl;
        
	std::string str13{std::string{"Hello"}.append(" World")};
	std::cout << "str13 : " << str13 << std::endl;
    */


	//Append can do more than the + operator
	//The + operator is just a convenience for basic concatenation
    /*
	std::cout << std::endl;
	std::cout << "Append method can do more than + operator : " << std::endl;
	std::string str14 {"Hello "};
	std::string str15 {str14.append(5,'?')}; // Appends 5 '?' characters
	std::cout << "str15 : " << str15 << std::endl;
		
		
	std::string str16{"The world is our shared home."};
	std::string str17{"Hello "};
	std::string str18{str17.append(str16,4,5)};// Append a sub-section of another string
												// starting from index 4 , 5 characters
	std::cout << "str18 : " << str18 << std::endl;
	
	//Direct output
	std::string str19{"Hello "};
	std::cout << "Direct output : " << str19.append(str16,4,5) << std::endl;
    */


	//Concatenating strings and characters
    /*
	std::cout << std::endl;
	std::cout << "Concatenating strings and characters : " << std::endl;
	std::string str20 {"Hello"};
	std::string str21 {"World"};
	std::string str22 {str20 + ' ' + str21};// The space in between is a character
	std::cout << "str22 : " << str22 << std::endl;

	std::string str23 = "Hello";
	(str23 += ',') += ' ';
	std::cout << "str23 : " << str23 << std::endl;

	//Another solution
	std::string str24 = "Hello"; // Take out the , and space we added before.
	std::string str25 {"I am here to see you."};
	std::string str26 {str24 + ',' + ' ' + str25};
	std::cout << "str26 : " << str26 << std::endl;
    */


	//Appending C-strings and char arrays
    /*
	std::cout << std::endl;
	std::cout << "Appending C-Strings and char arrays : "<<std::endl;
	const char message1[] {"World"};
	const char * message2 {"World"};
        
	std::cout <<" + char array : "  <<  std::string{"Hello "} + message1 << std::endl;
	std::cout <<" + C-String : "  <<  std::string{"Hello "} + message2 << std::endl;
	std::cout <<"append char array : "  <<  std::string{"Hello "}.append(message1) << std::endl;
	std::cout <<"append C-String : "  <<  std::string{"Hello "}.append( message2)<< std::endl;
	*/

    //Concatenating std::strings and numbers
        
	std::string str26{"Hello"};
        
	str26 += std::to_string(67.5f); // Treats 67 as a character code
					// When using the += operator, C++ knows to treat the 
					//integer operand as a character code and append that to our
					//std::string. But what if we want the 67 appended to std::string
					//literally
    std::cout << "str26 : " << str26 << std::endl;




    
    return 0;
}