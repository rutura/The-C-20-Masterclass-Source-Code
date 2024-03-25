#include <fmt/format.h>
#include "compare.h" // Preprocessor
#include "operations.h"


int main(){

    int maximum = max(134,56);
    fmt::println( "max : {}" , maximum );

    int minimum = min(146,23);
    fmt::println( "min : {}" , minimum );

    int x{4}; // 5
    int y{5}; // 6

    int result = incr_mult(x,y);
    fmt::println( "result : {}" , result );
   
    return 0;
}

