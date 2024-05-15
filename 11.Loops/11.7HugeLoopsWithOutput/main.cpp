#include <fmt/format.h>

int main()
{

  /*
  for(size_t i{0} ; i < 100000 ; ++i){
      //fmt::println( "i : {}" , i );
  }
  fmt::println( "Done!" );
  */

  size_t i{ 0 };// Iterator

  while (i < 100000) {
    // fmt::println( "i : {}" , i );
    ++i;
  }
  fmt::println("Done!");

  return 0;
}