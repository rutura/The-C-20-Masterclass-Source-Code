#include <fmt/format.h>
#include <string>

int main()
{

  /*std::string str1 {"Hello there"};

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
      fmt::println(""); */

  // Can also use range based for loop
  /*
  std::string str1 {"Hello there"};
  fmt::println( std::endl;
  fmt::println( "Using range based for loop : ");

      fmt::println( "str1(range based for loop) : " ;
  for(char value : str1){
      fmt::println( " {}" , value ;
  }
      fmt::println( std::endl;
  */

  // at() syntax to target characters
  /*fmt::println("");
  fmt::println( "Using the std::string::at() method : ");

  std::string str1 {"Hello there"};
      fmt::println( "str1 : (for loop with at()) : ") ;

  for(size_t i{}; i < str1.size(); ++i){
      fmt::print( " {}" , str1.at(i));
  }
      fmt::println("");*/

  // Modifying with operator[] and at()
  /*
  std::string str1 {"Hello there"};
  str1[0] = 'B';
  str1.at(1) = 'a';
  fmt::println( "str1(modified) : {}" , str1 );
  */

  // Getting the front and back characters
  /*std::string str2{"The Phoenix King"};
  char& front_char = str2.front();
  char& back_char = str2.back();
  fmt::println( "The front char in str2 is : {}" , front_char );
  fmt::println( "The back char in str2 is : {}" , back_char );

  front_char = 'r';
  back_char = 'd';

  fmt::println( "str2 : {}" , str2 );*/


  // c_str method
  /*
      //doc : https://en.cppreference.com/w/cpp/string/basic_string/c_str
      //returns const char * to the wrapped string. You shouldn't use
      //it to modify data in the string.
  std::string str2{"The Phoenix King"};
  const char * wrapped_c_string = str2.c_str();
  fmt::println( "Wrapped c string : {}" , wrapped_c_string );
  //wrapped_c_string[0] = 'e'; // Compiler error
  */

  // data()
  std::string str2{ "Hello World" };

  char *data = str2.data();
  fmt::println("Wrapped c string : {}", data);

  data[0] = 'B';// This also changes std::string.

  fmt::println("Wrapped c string (after modification) : {}", data);
  fmt::println("Original string (after modification ) :{}", str2);


  return 0;
}