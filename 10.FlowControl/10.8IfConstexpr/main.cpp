#include <fmt/format.h>


int main(){
   
   constexpr bool condition {false};

   if constexpr (condition){
       fmt::println( "Condition is true" );
   }else{
       fmt::println( "Condition is false" );
   }
    return 0;
}