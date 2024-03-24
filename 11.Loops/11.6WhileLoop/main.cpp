#include <fmt/format.h>

int main(){

	//Print I love C++ 10 times
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


    const size_t COUNT{100};
    size_t i{0}; // Iterator declaration

    while(i < COUNT ){ // Test
       fmt::println( "{} : I love C++", i );

       ++i; // Incrementation 
    }
    fmt::println( "Loop done!" );
   
    return 0;
}