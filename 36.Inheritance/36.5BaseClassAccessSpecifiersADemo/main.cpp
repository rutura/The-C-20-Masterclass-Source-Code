#include <fmt/format.h>
#include "person.h"
#include "player.h"
#include "nurse.h"
#include "engineer.h"

int main(){

    Person person1("Daniel Gray",27,"Blue Sky St 233 #56");
    fmt::println( "person1 : {}" , person1 );

    fmt::println( "---------------" );

    Player player;
    player.m_full_name = "Samuel Jackson";
    //player.m_age = 55; Compier error
    //player.m_address = "2i892317322"; Compiler

    fmt::println( "------------------" );

    Nurse nurse1;
    //nurse1.m_full_name = "Davy Johnes";Compiler error
    //nurse1.m_age = 51; // Compiler error

    fmt::println( "---------------" );
    Engineer engineer1;
    //engineer1.m_full_name = "Olivier Godson"; // Compiler error
    //engineer1.m_age = 55; // Compiler error
    //engineer1.m_address = "dsakfd;aslfjd;laskf"; // Compiler error
   
    return 0;
}