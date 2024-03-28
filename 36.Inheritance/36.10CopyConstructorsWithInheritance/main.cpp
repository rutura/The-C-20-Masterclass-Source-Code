#include "person.h"
#include "engineer.h"
#include "civilengineer.h"

int main(){
   
	/*
	Engineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12);

	fmt::println( "----------" );

	Engineer eng2(eng1);
	fmt::println( "eng2 : {}",eng2);
	*/

	CivilEngineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12,"Road Strength");

	fmt::println( "----------" );

	CivilEngineer eng2(eng1);
	fmt::println( "eng2 : {}" , eng2 );


    return 0;
}