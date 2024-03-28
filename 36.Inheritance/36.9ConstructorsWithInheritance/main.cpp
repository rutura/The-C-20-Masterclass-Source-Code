#include <iostream>
#include "person.h"
#include "engineer.h"
#include "civilengineer.h"

int main(){
    /*
	Person person1("John Snow",27,"Winterfell Cold 33St#75");
	fmt::println( "person1 : {}" , person1 );
    */

   /*
	fmt::println( "---------------------");
	Engineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12);
	fmt::println( "eng1 : {}" , eng1 );
    */

	fmt::println( "---------------------" );
	CivilEngineer civil_eng1("John Travolta",51,"Tiny Dog 42St#89",31,"Road Strength");
	fmt::println( "civil_eng1 : {}" , civil_eng1 );
	

    return 0;
}