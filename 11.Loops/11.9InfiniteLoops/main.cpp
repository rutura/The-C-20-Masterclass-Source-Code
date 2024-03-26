#include <fmt/format.h>


int main(){
   

   //Infinite loop : for loop
   /*
   for(size_t i{};true ; ++i){
       fmt::println( "{} : I love C++", i);
   }
   */

    //Infinite loop : while loop
    /*
    size_t i{0};

    while(true){
    fmt::println( "{} : I love C++", i);
        ++i;
    }
    */


    //Infinite loop : do while loop

    size_t i{0};

    do{
        fmt::println( "{} : I love C++", i);
        ++i;
    }while(true);
    
    return 0;
}