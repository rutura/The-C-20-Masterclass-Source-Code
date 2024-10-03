module;

#include <iostream>
#include <string_view>
#include <fmt/format.h>

export module utilities;

import inh_poly_1;
import inh_poly_2;
import inh_poly_3;
import inh_poly_4;
import inh_poly_5;


//#1: Inheritance basics
export void inh_poly_1_demo(){
	inh_poly_1::Player p1("Basketball");
	p1.set_first_name("John");
	p1.set_last_name("Snow");
	std::cout << "player: " << p1 << "\n";
}


//#2: Protected members
export void inh_poly_2_demo(){
	inh_poly_2::Player p1("Basketball", "John", "Snow");
	std::cout << "player: " << p1 << "\n";
}

//#3: Base class access specifiers
export void inh_poly_3_demo(){
	inh_poly_3::Person person1("Daniel Gray", 27, "Blue Sky St 233 #56");
	std::cout << "Person: " << person1 << "\n";

	fmt::println("---------------");

	inh_poly_3::Player player;
	player.m_full_name = "Samuel Jackson";
	// player.m_age = 55; Compier error
	// player.m_address = "2i892317322"; Compiler

	fmt::println("------------------");

	inh_poly_3::Nurse nurse1;
	// nurse1.m_full_name = "Davy Johnes";Compiler error
	// nurse1.m_age = 51; // Compiler error

	fmt::println("---------------");
	inh_poly_3::Engineer engineer1;
	// engineer1.m_full_name = "Olivier Godson"; // Compiler error
	// engineer1.m_age = 55; // Compiler error
	// engineer1.m_address = "dsakfd;aslfjd;laskf"; // Compiler error
}

//#4: Deep into private inheritance
export void inh_poly_4_demo(){
	inh_poly_4::Engineer eng1;
	inh_poly_4::CivilEngineer ce1;
	fmt::println("Done");
}

//#5: Resurecting members back in context
export void inh_poly_5_demo(){
	inh_poly_5::Engineer eng1;
	inh_poly_5::CivilEngineer ce1;
	fmt::println("Done");

}
