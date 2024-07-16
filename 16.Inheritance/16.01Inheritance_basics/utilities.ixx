module;

#include <iostream>
#include <string_view>
#include <fmt/format.h>

export module utilities;

import inh_basics;
import protected_members;
import base_acc_spec;

//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void inheritance_basics(){
	inh_basics::Player p1("Basketball");
	p1.set_first_name("John");
	p1.set_last_name("Snow");
	std::cout << "player: " << p1 << "\n";
}

export void protected_members_func(){
	protected_members::Player p1("Basketball", "John", "Snow");
	std::cout << "player: " << p1 << "\n";
}

export void base_access_specifiers(){
	base_acc_spec::Person person1("Daniel Gray", 27, "Blue Sky St 233 #56");
	std::cout << "Person: " << person1 << "\n";

	fmt::println("---------------");

	base_acc_spec::Player player;
	player.m_full_name = "Samuel Jackson";
	// player.m_age = 55; Compier error
	// player.m_address = "2i892317322"; Compiler

	fmt::println("------------------");

	base_acc_spec::Nurse nurse1;
	// nurse1.m_full_name = "Davy Johnes";Compiler error
	// nurse1.m_age = 51; // Compiler error

	fmt::println("---------------");
	base_acc_spec::Engineer engineer1;
	// engineer1.m_full_name = "Olivier Godson"; // Compiler error
	// engineer1.m_age = 55; // Compiler error
	// engineer1.m_address = "dsakfd;aslfjd;laskf"; // Compiler error
}
