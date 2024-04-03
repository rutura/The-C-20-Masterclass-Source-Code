#include <fmt/format.h>

int main()
{

  const size_t COUNT{ 5 };

  /*
  // For loops


      fmt::println( "Incrementing for loop : " );
  for (size_t i{} ; i < COUNT ; ++i){
      fmt::println( "i  : {}", i );
  }


      fmt::println( "Decrementing for loop : " );

  for(size_t i{COUNT} ; i > 0 ; --i){
      fmt::println( "i : {}", i );
  }
  */

  // Range based for loops can't be made to run in reverse order


  // While loop
  /*
  //Incrementing while
      fmt::println( "Incrementing while" );

  size_t i{0};

  while( i < COUNT){
      fmt::println( "i : {}", i );
      ++i;
  }

  //Decrementing while
      fmt::println( "Decrementing while : " );
  i = COUNT;

  while( i > 0){
      fmt::println( "i : {}", i );
      --i;
  }
  */

  // Do while loop
  /*
      //Incrementing do while
      fmt::println( "Incrementing do while" );
  size_t i = 0;

  do {
      fmt::println( "i : {}", i );
      ++i;

  }while ( i < COUNT);


  //Decrementing do while
      fmt::println( "Decrementing do while" );
  i = COUNT;

  do {
      fmt::println( "i : {}", i );
      --i;
  }while ( i > 0);
  */


  // Infinite loop
  // Decrementing do while
  fmt::println("Decrementing do while");
  unsigned int i = COUNT;

  do {
    fmt::println("i : {}", i);
    --i;
  } while (i >= 0);

  return 0;
}