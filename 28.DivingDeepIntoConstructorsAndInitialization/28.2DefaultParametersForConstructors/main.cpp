#include <fmt/format.h>
#include "cylinder.h"


int main(){

    Cylinder c1(4);
    fmt::println( "volume : {}" , c1.volume() );
   
    return 0;
}