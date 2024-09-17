module;

#include <fmt/format.h>
#include <cstring>

export module handling_c_strings;

namespace handling_c_strings
{

    export void cstring_strlen(){
        //std::strlen : Find the length of a string
        // real arrays and those decayed into pointers
        const char message1 [] {"The sky is blue."};

        //Array decays into pointer when we use const char*
        const char* message2 {"The sky is blue."};
        fmt::println( "message1 : {}",  message1 );
        fmt::println( "message2 : {}",  message2 );

        //strlen ignores null character
        fmt::println( "strlen(message1) : {}", std::strlen(message1) );

        // std::sizeof includes the null character
        fmt::println( "sizeof(message1) : {}",  sizeof(message1) );

        //strlen still works with decayed arrays
        fmt::println( "strlen(message2) : {}" , std::strlen(message2) );

        //std::size prints size of pointer
        fmt::println( "sizeof(message2) : {}",  sizeof(message2) );
    }

    export void cstring_strcmp(){

        // std::strcmp - signature : int strcmp( const char *lhs, const char *rhs );
        // Returns negative value if lhs appears before rhs in lexicographical order,
        // Zero if lhs and rhs compare equal.
        // and Positive value if lhs appears after rhs in lexicographical order.
        fmt::println("");
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

        //string_data3 = "Alabama"; // Error: can't directly assign to a static array
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
        fmt::println( "std::strcmp ({}, {}): {}", string_data1 , string_data2 , std::strcmp(string_data1, string_data2) );
    }

    export void cstring_strncmp(){
        // std::strncmp : int strncmp( const char *lhs, const char *rhs, std::size_t count );
        // Compares n characters in the strings
        // Returns : Negative value if lhs appears before rhs in lexicographical order.
        // Zero if lhs and rhs compare equal, or if count is zero.
        // Positive value if lhs appears after rhs in lexicographical order.
        // Print out the comparison

        const char* string_data1{ "Alabama" };
        const char* string_data2{ "Blabama" };
        size_t n{3};
        fmt::println("");
        fmt::println( "std::strncmp: " );
        fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,
                    std::strncmp(string_data1,string_data2,n) );

        string_data1 = "aaaia";
        string_data2 = "aaance";

        fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,
                    std::strncmp(string_data1,string_data2,n) );

        n = 5;

        fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,
                    std::strncmp(string_data1,string_data2,n) );

        string_data1 = "aaaoa";
        string_data2 = "aaance";

        fmt::println( "std::strncmp ({}, {}, {}): {}", string_data1, string_data2, n,
                    std::strncmp(string_data1,string_data2,n) );
    }

    export void cstring_find_first_occurence_version_1(){
        // Find the first occurrence of a character
        // CODE STOLEN FROM THE DOCS :
        fmt::println("");
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
        fmt::println( "iterations : {}",  iterations );
    }

    export void cstring_find_first_occurence_version_2(){
        // A lesser version that will loop 25 times
        // Find the first occurrence of a character
        // CODE STOLEN FROM THE DOCS :
        fmt::println("");
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
        fmt::println( "iterations : {}", iterations );
    }

    export void cstring_find_last_occurence(){
        // Find last occurence
        // CODE STOLEN FROM THE DOCS :
        fmt::println("");
        fmt::println("std::strrchr : ");
        // doc : https://en.cppreference.com/w/cpp/string/byte/strrchr

        char input[] = "/home/user/hello.cpp";
        char *output = std::strrchr(input, '/');
        if (output)
            fmt::println("{}", output + 1);//+1 because we want to start printing past
                                        // the character found by std::strrchr.	
    }

    export void cstring_concatenation_version_1(){
        // Concatenation
        fmt::println("");
        fmt::println("std::strcat : " );
        //doc : https://en.cppreference.com/w/cpp/string/byte/strcat

        char dest[50] = "Hello ";
        char src[50] = "World!";
        std::strcat(dest, src); // Some compilers (MSVC) think these functions are unsafe!
        fmt::println( "dest : {}" , dest ); // Hello World
        std::strcat(dest, " Goodbye World!");
        fmt::println( "dest : {}",dest ); // Hello World Goodbye World!
    }

    export void cstring_concatenation_version_2(){
        // More concatenation
        fmt::println("");
        fmt::println( "More std::strcat : " );

        char *dest1 = new char[30]{'F','i','r','e','l','o','r','d','\0'};
        char *source1 =
            new char[30]{',','T','h','e',' ','P','h','e','n','i','x',' ','K','i','n','g','!','\0'};

        //NOTE TO SELF :
            //Describe what's going to happen in std::strcat before you do the cat :
            //source is going to be appended to dest, and the process
            //will start by overriding the null character in dest

        fmt::println( "std::strlen(dest1) :{}",  std::strlen(dest1) );
        fmt::println( "std::strlen(source1) : {}", std::strlen(source1) );

        fmt::println( "Concatenating..." );
        std::strcat(dest1,source1);

        fmt::println( "std::strlen(dest1) : {}",std::strlen(dest1) );
        fmt::println( "dest1 : {}",  dest1 );
    }


    export void cstring_strncat(){
        // std::strncat  : concatenates n characters from src to dest and
        // returns a pointer to the result string
        // signature : char *strncat( char *dest, const char *src, std::size_t count );
        fmt::println("");
        fmt::println( "std::strncat:" );
        char dest2[50] { "Hello" };

        char source2[30] = {" There is a bird on my window"};

        //You can even use the returned pointer immediately for print out
        //This is a pattern you'll see a lot in C++ code out there.
        //This works for std::cout but not for fmt::println
        //fmt::println( std::strncat(dest2,source2,6) ); //Error

        //Or you can do std::strncat separately and print dest2
        std::strncat(dest2,source2,6);
        fmt::println( "The concatenated string is : {}",  dest2 );
    }

    export void cstring_strcpy(){
        // std::strcpy - signature : char* strcpy( char* dest, const char* src );
        fmt::println( "std::strcpy : " );
        const char* source3 = "C++ is a multipurpose programming language.";
        char *dest3 = new char[std::strlen(source3) + 1];// +1 for the null character
                                                        //Contains garbage data
                                                        //Not initialized

        std::strcpy(dest3,source3);

        fmt::println( "sizeof(dest3) : {}",  sizeof(dest3) );
        fmt::println( "std::strlen(dest3) : {}",  std::strlen(dest3) );
        fmt::println( "dest3 : {}",  dest3 );
    }

    export void cstring_strncpy(){
        // std::strncpy : Copy n characters from src to dest -
        // signature : char *strncpy( char *dest, const char *src, std::size_t count );
        fmt::println("");
        fmt::println("std::strncpy:");
        const char *source4 = "Hello";
        char dest4[] = { 'a', 'b', 'c', 'd', 'e', 'f', '\0' };// Have to put the terminating
                                                                // null char if we want to print

        fmt::println("dest4 : {}", dest4);

        fmt::println("Copying...");
        std::strncpy(dest4, source4, 5);

        fmt::println("dest4 : {}", dest4);
    }

    
} // namespace handling_c_strings
