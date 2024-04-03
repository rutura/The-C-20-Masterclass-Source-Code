#include <fmt/format.h>

int main()
{

  // Print I love C++ 10 times : The bad way
  /*
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  fmt::println( "I love C++" );
  */

  // for loop : the good way
  /*
 for( unsigned int i{0} ; i < 10000 ;++i){
     //Whatever we want the loop to run
     fmt::println("{} : I love C++", i );
 }
 fmt::println( "Loop done!" );
 */

  // Use size_t : a representation of some unsigned int for positive numbers [sizes]
  /*
  for(size_t i{0} ; i < 10 ; ++i){
      fmt::println( " {} : I love C++", i );
  }
  fmt::println( "Loop done!" );
  */
  /*
  //sizeof(size_t)
  fmt::println( "sizeof(size_t) : {}" , sizeof(size_t) );
  */


  // Scope of the iterator
  /*
  for(size_t i{0} ; i < 10 ; ++i){
      fmt::println( "{} : I love C++", i );
  }
  fmt::println( "Loop done!" );
  // fmt::println( "i : {}", i ); //Compiler error : i is not in scope
  */


  // Iterator declared outside the loop
  /*
   size_t i{0}; // Iterator defined outside

   for(i ; i < 10 ; ++i){
       fmt::println( " {}: I love C++", i );
   }
   fmt::println( "Loop done!" );
   fmt::println( "i : {}",  i );
   */


  // Leave out the iterator declaration part
  /*
  size_t i{0}; // Iterator defined outside

  for(  ; i < 10 ; ++i){
      fmt::println( " {}: I love C++", i );
  }
  fmt::println( "Loop done!" );
  fmt::println( "i : {}",  i );
  */


  // Don't hard code values : BAD!

  const size_t COUNT{ 100 };

  for (size_t i{ 0 }; i < COUNT; ++i) { fmt::println(" {}: I love C++", i); }
  fmt::println("Loop done!");

  return 0;
}