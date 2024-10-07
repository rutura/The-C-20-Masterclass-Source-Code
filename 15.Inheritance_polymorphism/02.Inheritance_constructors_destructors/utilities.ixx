module;

#include <string_view>
#include <fmt/format.h>
#include <iostream>

export module utilities; 

import inh_poly_1;
import inh_poly_2;
import inh_poly_3;
import inh_poly_4;

//#1: The order of constructor and destructor calls in inheritance
export void inh_poly_1_demo(){
	//Default construct
	inh_poly_1::CivilEngineer eng1;
	fmt::println("eng1 : {}", eng1.get_info());
	fmt::println("");

	//Parameterized construction
	inh_poly_1::CivilEngineer eng2("Daniel Gray", 41, "Green Sky Oh Blue 33St#75", 12, "Road Strength");
	fmt::println("eng2 : {}", eng2.get_info());
	fmt::println("");

	//Set up a person object
	inh_poly_1::Person person1("John Snow", 27, "Winterfell Cold 33St#75");
	fmt::println("person1 : {}", person1.get_info());
	fmt::println("");
}

//#2: Copy constructors, copy assignment operators with inheritance
export void inh_poly_2_demo(){

	fmt::println("\n--- Creating Person p1 ---");
    inh_poly_2::Person p1{"John Doe", 30, "123 Main St"};
    fmt::println("\n--- Copying Person p1 to p2 ---");
    inh_poly_2::Person p2{p1};
    fmt::println("\n--- Assigning p1 to p3 ---");
    inh_poly_2::Person p3;
    p3 = p1;
	//Print person info
	fmt::println("\n--- Printing Person info ---");
	fmt::println("p1: {}", p1.get_info());
	fmt::println("p2: {}", p2.get_info());
	fmt::println("p3: {}", p3.get_info());

    fmt::println("\n--- Creating Engineer e1 ---");
    inh_poly_2::Engineer e1{"Jane Smith", 40, "456 Elm St", 5};
    fmt::println("\n--- Copying Engineer e1 to e2 ---");
    inh_poly_2::Engineer e2{e1};
    fmt::println("\n--- Assigning e1 to e3 ---");
    inh_poly_2::Engineer e3;
    e3 = e1;
	//Print engineer info
	fmt::println("\n--- Printing Engineer info ---");
	fmt::println("e1: {}", e1.get_info());
	fmt::println("e2: {}", e2.get_info());
	fmt::println("e3: {}", e3.get_info());

	fmt::println("\n--- Creating CivilEngineer ce1 ---");
    inh_poly_2::CivilEngineer ce1{"Alex Johnson", 50, "789 Oak St", 10, "Structural"};
    fmt::println("\n--- Copying CivilEngineer ce1 to ce2 ---");
    inh_poly_2::CivilEngineer ce2{ce1};
    fmt::println("\n--- Assigning ce1 to ce3 ---");
    inh_poly_2::CivilEngineer ce3;
    ce3 = ce1;
	//Print civil engineer info
	fmt::println("\n--- Printing CivilEngineer info ---");
	fmt::println("ce1: {}", ce1.get_info());
	fmt::println("ce2: {}", ce2.get_info());
	fmt::println("ce3: {}", ce3.get_info());

}

//#3: Inheriting base constructors
export void inh_poly_3_demo(){
	inh_poly_3::Engineer eng1("Daniel Gray", 41, "Green Sky Oh Blue 33St#75");
	fmt::println("eng1 : {}", eng1.get_info());
}


//#4: Member hiding in inheritance
export void inh_poly_4_demo(){
	inh_poly_4::Parent parent1;
	parent1.print_var();	// Calls Parent's print_var

	fmt::println("");

	inh_poly_4::Child child1;
	child1.print_var();		// Calls Child's print_var
	child1.Parent::print_var();	// Calls Parent's print_var
	child1.show_values();	// Calls Child's show_values, which in turn accesses Parent's m_member_var
}