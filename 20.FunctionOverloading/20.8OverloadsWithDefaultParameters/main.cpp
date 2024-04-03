#include <fmt/format.h>

// Declarations
// void print_age(int age = 33);

void print_age(long int age = 44);

int main()
{


  print_age();


  return 0;
}

// Definitions
// void print_age(int age ){
//     fmt::println( "Your age is( int version)  : {}" , age );
// }

void print_age(long int age) { fmt::println("Your age is (long int version) : {}", age); }
