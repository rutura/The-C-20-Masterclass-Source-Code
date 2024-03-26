#include <fmt/format.h>
#include <cstring>

int main(){

	/*//std::strlen : Find the length of a string
    // real arrays and those decayed into pointers
    const char message1 [] {"The sky is blue."};
	
	//Array decays into pointer when we use const char*
	const char* message2 {"The sky is blue."};
    fmt::println( "message1 : {}",  message1 );
	
	//strlen ignores null character
    fmt::println( "strlen(message1) : {}", std::strlen(message1) );
	
	// Includes the null character
    fmt::println( "sizeof(message1) : {}",  sizeof(message1) );
	
	//strlen still works with decayed arrays
	fmt::println( "strlen(message2) : {}" , std::strlen(message2) );
	
	//Prints size of pointer
    fmt::println( "sizeof(message2) : {}",  sizeof(message2) );*/


   //std::strcmp - signature : int strcmp( const char *lhs, const char *rhs );
    //Returns negative value if lhs appears before rhs in lexicographical order,
    //Zero if lhs and rhs compare equal.
    //and Positive value if lhs appears after rhs in lexicographical order. 
    /*fmt::println("");
    fmt::println( "std::strcmp : " );
    const char* string_data1{ "Alabama" };
    const char* string_data2{ "Blabama" };

    char string_data3[]{ "Alabama" };
    char string_data4[]{ "Blabama" };

    //Print out the comparison
    fmt::println( "std::strcmp ({} ,{} ) : {}",  string_data1 , string_data2, std::strcmp(string_data1, string_data2) );

    fmt::println( "std::strcmp ({}, {}): {}" , string_data3 , string_data4,  std::strcmp(string_data3, string_data4) );


    string_data1 = "Alabama";
    string_data2 = "Alabamb";

    //string_data3 = "Alabama";
    //string_data4 = "Alabamb";

    //Print out the comparison
    fmt::println( "std::strcmp ({}, {} ) : {}",string_data1,  string_data2,  std::strcmp(string_data1, string_data2) );


        string_data1 = "Alacama";
    string_data2 = "Alabama";

    //Print out the comparison
    fmt::println( "std::strcmp ({}, {}) : {}", string_data1 ,  string_data2 , std::strcmp(string_data1, string_data2) );

    string_data1 = "India";
    string_data2 = "France";

    //Print out the comparison
    fmt::println( "std::strcmp ({}, {}) : {}", string_data1,  string_data2, std::strcmp(string_data1, string_data2) );

    string_data1 = "Kigali";
    string_data2 = "Kigali";

    //Print out the comparison
    fmt::println( "std::strcmp ({}, {}): {}", string_data1 , string_data2 , std::strcmp(string_data1, string_data2) );*/


	//std::strncmp : int strncmp( const char *lhs, const char *rhs, std::size_t count );
	//Compares n characters in the strings
	//Returns : Negative value if lhs appears before rhs in lexicographical order.
    //Zero if lhs and rhs compare equal, or if count is zero.
    //Positive value if lhs appears after rhs in lexicographical order. 
    //Print out the comparison

    /*
    const char* string_data1{ "Alabama" };
    const char* string_data2{ "Blabama" };
    size_t n{3};
    fmt::println("");
    fmt::println( "std::strncmp : " );
    fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,  std::strncmp(string_data1,string_data2,n) );
              
    string_data1 = "aaaia";
    string_data2 = "aaance";

	fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,  std::strncmp(string_data1,string_data2,n) );
              
    n = 5;

	fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,  std::strncmp(string_data1,string_data2,n) );
              
    string_data1 = "aaaoa";
    string_data2 = "aaance";

	fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,  std::strncmp(string_data1,string_data2,n) );
	*/




    //Find the first occurrence of a character 
	//CODE STOLEN FROM THE DOCS : 
    /*fmt::println("");
    fmt::println( "std::strchr : " );
	//doc : https://en.cppreference.com/w/cpp/string/byte/strchr
    
	//we use std::strchr to find all the characters one by one.

	const char * const str { "Try not. Do, or do not. There is no try."};
    //Can make this a const pointer to prevent users from making it point somewhere else
	char target = 'T';
	const char *result = str;
	size_t iterations{};
	
 
	while ((result = std::strchr(result, target)) != nullptr) {
		fmt::println( "Found '{}' starting at '{}'", target, result);
 
		// Increment result, otherwise we'll find target at the same location
		++result;
		++iterations;
	}
	fmt::println( "iterations : {}",  iterations );*/


    //A lesser version that will loop 25 times
	//Find the first occurrence of a character
	//CODE STOLEN FROM THE DOCS : 
	/*fmt::println("");
	fmt::println( "std::strchr : " );
	//doc : https://en.cppreference.com/w/cpp/string/byte/strchr

	//we use std::strchr to find all the characters one by one.

	const char* str{ "Try not. Do, or do not. There is no try." };
	char target = 'T';
	const char* result{ nullptr };
	size_t iterations{};


	while ((result = std::strchr(str, target)) != nullptr) {
		fmt::println( "Found '{}' starting at '{}'", target, result);

		// Increment result, otherwise we'll find target at the same location
		++str; // Making the pointer point to the next character
		++iterations;
	}
	fmt::println( "iterations : {}", iterations );*/


	//Find last occurence
	//CODE STOLEN FROM THE DOCS : 
    fmt::println("");
    fmt::println( "std::strrchr : " );
	//doc : https://en.cppreference.com/w/cpp/string/byte/strrchr
	
    char input[] = "/home/user/hello.cpp";
    char* output = std::strrchr(input, '/');
    if(output)
        fmt::println( "{}", output+1 ); //+1 because we want to start printing past
                                            // the character found by std::strrchr.
   
    return 0;
}