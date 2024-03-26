#include <fmt/format.h>

int main(){

    int scores [] {1,2,5};

   
    int count { std::size(scores)}; // std::size( C++17)

    fmt::println( "sizeof(scores) : {}" , sizeof(scores) );
    fmt::println( "sizeof(scores[0]) : {}" ,  sizeof(scores[0]) );
    fmt::println( "count : {}" , count );



    /*
    int count {sizeof(scores)/sizeof(scores[0])};


    for(size_t i {0} ; i < count ; ++i){
        fmt::println( "scores [{}] : {}",i , scores[i] );
    }
 

   //Range based for loop
    for ( auto i : scores){
            fmt::println( "value  : {}" , i );
    }
    */
   
    
    return 0;
}