#include <fmt/format.h>
#include "cylinder.h"


int main(){
   Cylinder c1(5);
   fmt::println( "base_rad : {}" , c1.get_base_radius() );
   fmt::println( "height : {}" , c1.get_height() );
   fmt::println( "volume : {}" , c1.volume() );
    return 0;
}