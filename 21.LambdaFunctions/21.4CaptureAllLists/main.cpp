#include <fmt/format.h>


int main()
{

  // Capture everything by value
  /*
   int c{42};

   auto func = [=](){
       fmt::println("Inner value : {}" , c );
   };

   for(size_t i{} ; i < 5 ;++i){
       fmt::println("Outer value : {}" , c );
       func();
       ++c;
   }
   */


  // Capturing all reference
  int c{ 42 };
  int d{ 5 };

  auto func = [&]() {
    fmt::println("Inner value : {}", c);
    fmt::println("Inner value(d) : {}", d);
  };

  for (size_t i{}; i < 5; ++i) {
    fmt::println("Outer value : {}", c);
    func();
    ++c;
  }

  return 0;
}