#include <fmt/format.h>

int main()
{

  // Declare array
  char message[5]{ 'H', 'e', 'l', 'l', 'o' };
  // int data[5] {1,2,3,3,3};

  // fmt::println( "data : {}",  data );


  // Print out the array through looping
  /*
  fmt::println( "message : ");
  for( auto c : message){
      fmt::println( c );
  }
  */


  /*
   //Change characters in our array
   message[1] = 'a';

   //Print out the array through looping
   fmt::println( "message : ");
   for( auto c : message){
       fmt::println( c );
   }
   */


  // Will probably print garbage after your char array
  /*
  fmt::println( "message : {}", message );
  */


  // If a character array is null terminated, it's called as C-String
  /*
  char message1 [] {'H','e','l','l','o','\0'};
  fmt::println( "message1 : {}", message1 );
  fmt::println( "sizeof(message1) : {}", sizeof(message1) );
  */


  /*
   char message2 [6] {'H','e','l','l','o'};
   fmt::println( "message2 : {}", message2 );
   fmt::println( "sizeof(message2) : {}", sizeof(message2) );

   char message3 [] {'H','e','l','l','o'}; // This is not a c string ,
                                                                                       //as there is not null character
   fmt::println( "message3 : {}", message3 );
   fmt::println( "sizeof(message3) : {}", sizeof(message3) );
   */


  // String literal
  /*
  char message4 [] {"Hello"};
  fmt::println( "message4 : {}", message4 );
  fmt::println( "sizeof(message4) : {}", sizeof(message4) );
  */


  // Can't safely print out arrays other than those of characters
  int numbers[]{ 1, 2, 3, 4, 5 };
  fmt::println("numbers :  {}", numbers);// error


  return 0;
}