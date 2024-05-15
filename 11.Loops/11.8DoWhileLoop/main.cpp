#include <fmt/format.h>

int main()
{

  // Print I love C++ 10 times
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

  const int COUNT{ 0 };
  size_t i{ 0 };// Iterator declaration

  do {
    fmt::println("{} : I love C++", i);
    ++i;// Incrementation
  } while (i < COUNT);

  fmt::println("Loop done!");

  return 0;
}