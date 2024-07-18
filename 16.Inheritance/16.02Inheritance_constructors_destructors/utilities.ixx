module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import inh_default_arg_constr;
import constr_and_inh;
import copy_constr_and_inh;
import inherit_base_constructors;
import inh_and_destructors;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void inheritance_with_default_arg_constructors(){
	inh_default_arg_constr::CivilEngineer ce1;
}

export void constructors_and_inheritance(){
    /*
    constr_and_inh::Person person1("John Snow",27,"Winterfell Cold 33St#75");
	std::cout << "person1 : " << person1 << "\n";
	*/

    /*
    fmt::println( "---------------------");
    constr_and_inh::Engineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12);
	std::cout << "eng1 : " << eng1 << "\n";
	*/

  	/*
	fmt::println("---------------------");
	constr_and_inh::CivilEngineer civil_eng1("John Travolta", 51, "Tiny Dog 42St#89", 31, "Road Strength");
	std::cout << "civil_eng1 : " << civil_eng1 << "\n";
	*/
}

export void copy_constructors_and_inheritance(){
	
	copy_constr_and_inh::Engineer eng1("Daniel Gray",41,"Green Sky Oh Blue 33St#75",12);
	std::cout << "----" << "\n";

	copy_constr_and_inh::Engineer eng2(eng1);
	std::cout << "eng2 : " << eng2 << "\n";

	/*
	copy_constr_and_inh::CivilEngineer eng1("Daniel Gray", 41, "Green Sky Oh Blue 33St#75", 12, "Road Strength");

	copy_constr_and_inh::CivilEngineer eng2(eng1);
	std::cout << "eng2 : " << eng2 << "\n";
	*/
}


export void inheriting_base_constructors(){
	inherit_base_constructors::Engineer eng1("Daniel Gray", 23, "asdl;fkjdas;fkdas;fk", 4);
	std::cout << "eng1 : " << eng1 << "\n";
}

export void inheritance_and_destructors(){
	inh_and_destructors::CivilEngineer eng1("Daniel Gray", 41, "Green Sky Oh Blue 33St#75", 12, "Road Strength");
}