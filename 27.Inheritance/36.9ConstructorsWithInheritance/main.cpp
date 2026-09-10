#include <iostream>
#include "person.h"
#include "engineer.h"
#include "civilengineer.h"

int main(){
    /*
	Person person1("John Snow",27,"Winterfell Cold 33St#75");
	std::cout << "person1 : " << person1 << std::endl;
    */

   /*
	std::cout << "---------------------"<< std::endl;
	Engineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12);
	std::cout << "eng1 : " << eng1 << std::endl;	
    */

	std::cout << "---------------------" << std::endl;
	CivilEngineer civil_eng1("John Travolta",51,"Tiny Dog 42St#89",31,"Road Strength");
	std::cout << "civil_eng1 : " << civil_eng1 << std::endl;
	

    return 0;
}