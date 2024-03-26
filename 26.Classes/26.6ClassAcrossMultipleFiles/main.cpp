#include <fmt/format.h>
#include "cylinder.h"

int main(){
    Cylinder cylinder1(10,10);
    fmt::println( "volume : {}" , cylinder1.volume() );
    
    return 0;
}