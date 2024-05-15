#include "dog.h"
#include <fmt/format.h>

int main()
{

  Dog dog1("Fluffy", "Shepherd", 2);

  /*
      const std::string& str_ref = dog1.compile_dog_info();
      fmt::println( " info : {}" , str_ref );
  */

  unsigned int *int_ptr = dog1.jumps_per_minute();
  fmt::println("jumps_per_minute : {}", *int_ptr);

  fmt::println("Done!");
  return 0;
}