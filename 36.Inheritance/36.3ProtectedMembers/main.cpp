#include <fmt/format.h>
#include "player.h"


int main(){

    Player p1("Basketball","John","Snow");
    fmt::println( "player : {}" , p1 );
   
    return 0;
}