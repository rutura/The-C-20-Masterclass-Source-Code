#include <fmt/format.h>
#include "point.h"

int main(){

    Point p1(10,10);
    fmt::println( "p1 : {}" ,fmt::ptr(& p1 ));

    //++p1;
  
    operator++(p1);
    

    fmt::println( "p1 : {}" ,fmt::ptr(& p1 )); // 11

    for(size_t i{}; i < 20 ; ++i){
        ++p1;
        fmt::println( "p1 : {}" ,fmt::ptr(& p1 ));
    }
    
    return 0;
}