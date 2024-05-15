#include <cstring>
#include <fmt/format.h>

int main()
{

  // Concatenation
  /*
  fmt::println("");
  fmt::println("std::strcat : " );
  //doc : https://en.cppreference.com/w/cpp/string/byte/strcat

  char dest[50] = "Hello ";
char src[50] = "World!";
std::strcat(dest, src); // Some compilers (MSVC) think these functions are unsafe!
fmt::println( "dest : {}" , dest ); // Hello World
std::strcat(dest, " Goodbye World!");
fmt::println( "dest : {}",dest ); // Hello World Goodbye World!
*/


  // More concatenation
  /*fmt::println("");
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
fmt::println( "dest1 : {}",  dest1 );*/


  // std::strncat  : concatenates n characters from src to dest and
  // returns a pointer to the result string
  // signature : char *strncat( char *dest, const char *src, std::size_t count );
  /*fmt::println("");
  fmt::println( "std::strncat:" );
  char dest2[50] { "Hello" };

  char source2[30] = {" There is a bird on my window"};

  //You can even use the returned pointer immediately for print out
  //This is a pattern you'll see a lot in C++ code out there.
  fmt::println( std::strncat(dest2,source2,6) );

  //Or you can do std::strncat separately and print dest2
  std::strncat(dest2,source2,6);
  fmt::println( "The concatenated string is : {}",  dest2 );*/


  // std::strcpy - signature : char* strcpy( char* dest, const char* src );
  /*fmt::println("");
      fmt::println( "std::strcpy : " );
  const char* source3 = "C++ is a multipurpose programming language.";
  char *dest3 = new char[std::strlen(source3) + 1];// +1 for the null character
                                                                                                      //Contains garbage
  data
                                                                                                      //Not initialized

  std::strcpy(dest3,source3);

  fmt::println( "sizeof(dest3) : {}",  sizeof(dest3) );
  fmt::println( "std::strlen(dest3) : {}",  std::strlen(dest3) );
  fmt::println( "dest3 : {}",  dest3 );*/


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


  return 0;
}