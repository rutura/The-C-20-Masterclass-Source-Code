#include "player.h"


int main(){

    Player p1("Basketball");
    p1.set_first_name("John");
    p1.set_last_name("Snow");
    fmt::println( "player : {}",  p1);
   
    return 0;
}