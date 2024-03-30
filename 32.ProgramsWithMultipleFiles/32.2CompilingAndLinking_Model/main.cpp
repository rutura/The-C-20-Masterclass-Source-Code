#include <fmt/format.h>
#include "utilities.h"

int main(){

    double result = add(10.5,20.8);
    fmt::println( "result : {}" , result );
    
    return 0;
}