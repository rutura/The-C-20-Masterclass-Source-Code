#include <fmt/format.h>

int main()
{

  const size_t name_length{ 15 };

  char members[][name_length]{ { 'J', 'o', 'h', 'n' },
    {
      'S',
      'a',
      'm',
      'u',
      'e',
      'l',
    },
    { 'R', 'a', 's', 'h', 'i', 'd' },
    { 'R', 'o', 'd', 'r', 'i', 'g', 'e', 'z' } };

  // Declaring a 2D array

  // Printing out like this is unsafe : may go over and print
  // outside your valid memory block
  // until a terminating null character is encountered.
  /*fmt::println( "Unsafe printing of members : " );
for (size_t i {0}; i < std::size(members) ; ++i){
  fmt::println( "{}", members[i] );
}*/


  // Can loop around manually printing out each character
  /*fmt::println( "Printing out character by character manually : " );
  for (size_t i{0} ; i < std::size(members) ; ++i){
      for (size_t j{0} ; j < std::size(members[i]) ; ++j){
          fmt::println( "{}", members[i][j] );
      }
  }*/

  // Better : Using C-string litterals
  // Compared to initialization with charactes with in '', this
  //  is even easier to type. The entire string is a single entity
  // you can manage easily.
  /*char members1 [][name_length] {
      "John",
      "Samuel",
      "Rashid",
      "Rodriguez"
  };

  //Printing out members1
  fmt::println( "Printing out members1 (C-string literals) : " );
  for (size_t i {0}; i < std::size(members1) ; ++i){
      fmt::println( "{}", members1[i] );
  }*/


  // Updating our prediction declaration in the fortune teller game
  char predictions[][90]{ "a lot of kinds running in the backyard!",
    "a lot of empty beer bootles on your work table.",
    "you Partying too much with kids wearing weird clothes.",
    "you running away from something really scary",
    "clouds gathering in the sky and an army standing ready for war",
    "dogs running around in a deserted empty city",
    "a lot of cars stuck in a terrible traffic jam",
    "you sitting in the dark typing lots of lines of code on your dirty computer",
    "you yelling at your boss. And oh no! You get fired!",
    "you laughing your lungs out. I've never seen this before.",
    "Uhm , I don't see anything!"

  };

  fmt::println("Prediction : {}", predictions[5]);


  return 0;
}