#include <fmt/format.h>
#include <vector>


int main(){

    std::vector numbers {1,2,3,4,5,6,7,8,9,10};
    
    //Trying out reverse iterators
    //auto it = numbers.rbegin(); // A reverse iterator increments backwards from the end.
    auto it= numbers.rbegin();
    *it = 34;
    fmt::print( "Numbers : [");
    while(it != numbers.rend()){
        fmt::print( " {}" , *it) ;
        ++it;
    }
    fmt::println( "] " );

    fmt::println( "--------" );
    /*
    auto it_rev = numbers.rbegin();
    
    if( it_rev != numbers.end()){ // Compiler error.
        fmt::println( "Do something..." );
    }
    */
   
    return 0;
}