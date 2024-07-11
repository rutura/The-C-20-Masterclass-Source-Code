module;

#include <iostream>
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

import player;
import person;
import engineer;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1: Inheritance basics
/*
export void inheritance_basics(){
	Player p1("Basketball");
	p1.set_first_name("John");
	p1.set_last_name("Snow");
	std::cout << "p1 - " << p1 << "\n";
}
*/


//#2: Protected members
export void protected_members(){
	Player p1("Basketball", "John", "Snow");
	std::cout << "player: " << p1 << "\n";
}

//#3: Exploring base class access specifiers
export void base_class_access_specifiers(){

	Person1 person1("Daniel Gray", 27, "Blue Sky St 233 #56");
	std::cout << "person1: " << person1 << "\n";

	fmt::println("---------------");

	Player1 player;
	player.m_full_name = "Samuel Jackson";
	// player.m_age = 55; Compier error
	// player.m_address = "2i892317322"; Compiler

	fmt::println("------------------");

	Nurse nurse1;
	// nurse1.m_full_name = "Davy Johnes";Compiler error
	// nurse1.m_age = 51; // Compiler error

	fmt::println("---------------");
	Engineer engineer1;
	// engineer1.m_full_name = "Olivier Godson"; // Compiler error
	// engineer1.m_age = 55; // Compiler error
	// engineer1.m_address = "dsakfd;aslfjd;laskf"; // Compiler error
}


//#4: Private inheritance up close
//GCC doesn't like the idea of wrapping this in namespaces.

/*
export void private_inheritance_up_close(){

	Private_Inheritance_Up_Close::Engineer eng1;
	Private_Inheritance_Up_Close::CivilEngineer ce1;
	fmt::println("Done");

}
*/