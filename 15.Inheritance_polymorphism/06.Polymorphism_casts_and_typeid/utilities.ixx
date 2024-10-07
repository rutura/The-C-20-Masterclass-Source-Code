module;

#include <string_view>
#include <string>
#include <typeinfo>
#include <fmt/format.h>

export module utilities; 

import inh_poly_1;
import inh_poly_2;

//#1: Dynamic casts
export void inh_poly_1_demo(){

	using inh_poly_1::Animal;
	using inh_poly_1::Feline;
	using inh_poly_1::Dog;

	// Can't call a derived non-virtual function on a base class pointer
	Animal *animal1 = new Feline("stripes", "feline1");
	//animal1->do_some_feline_thingy(); // Won't work. do_some_feline_thingy() is not a virtual function coming  from Animal.



	//You can do that if you cast to a derived class pointer through dynamic_cast for virtual objects
	// If the cast succeeds, we get a valid pointer back,
	// if it fails, we get nullptr. So we can check before
	// calling stuff on the returned pointer
	Feline *feline_ptr = dynamic_cast<Feline *>(animal1);

	if (feline_ptr) {
		feline_ptr->do_some_feline_thingy();
	} else {
		fmt::println("Couldn't do the transformation from Animal* to Dog*");
	}



	// Base class reference
	Feline feline2("stripes", "feline2");
	Animal &animal_ref = feline2;


	// Calling non virtual methods on animal_ref won't work
	//animal_ref.do_some_feline_thingy();	// Won't work. do_some_feline_thingy() is not a virtual function coming  from Animal.

	//Casting can fail: We're trying to transform a Feline reference to a Dog reference
	//Dog & dog_ref {dynamic_cast<Dog&>(animal_ref)};
	//dog_ref.do_some_dog_thingy();	// This will crash at run time. Feline doesn't have any Dog information inside.



	// Doing proper checks with references
	Dog *dog_ptr_1{ dynamic_cast<Dog *>(&animal_ref) };
	if (dog_ptr_1) {
		dog_ptr_1->do_some_dog_thingy();
	} else {
		fmt::println("Couldn't cast to Dog reference,Sorry.");
	}

	//Doing the same through a few helper functions
	inh_poly_1::do_something_with_animal_ptr(animal1);
	inh_poly_1::do_something_with_animal_ref(animal_ref);

	delete animal1;	
}

export void inh_poly_2_demo(){

	// 1. typeid with fundamental types : returns static type
	fmt::println("typeid(int) : {}", typeid(int).name());
	if (typeid(22.2f) == typeid(float)) {
		fmt::println("22.2f is a float");
	} else {
		fmt::println("22.2f is not float");
	}

	fmt::println("----------------");
	// 2. typeid with references(polymorphic)
	fmt::println("Polymorphic references : ");
	inh_poly_2::DynamicDerived dynamic_derived;
	inh_poly_2::DynamicBase &base_ref = dynamic_derived;
	fmt::println("Type of dynamic_derived : {}", typeid(dynamic_derived).name());
	fmt::println("Type of base_ref : {}", typeid(base_ref).name());

	fmt::println("----------------");

	// 3. typeid with pointers(polymorphic)
	fmt::println("Polymorphic pointers : ");
	inh_poly_2::DynamicBase *b_ptr = new inh_poly_2::DynamicDerived;

	fmt::println("Type of b_ptr : {}", typeid(b_ptr).name());// static type

	// ATTENTION :
	//	For pointers you have to dereference to see the dynamic type //
	fmt::println("Type of *b_ptr : {}", typeid(*b_ptr).name());


	fmt::println("----------------");

	// 4. type id with non polymorphic pointers and refs : We'll get static types
	// because we're using static binding, the default behavior
	fmt::println("Non polymorphic pointers and refs : ");
	inh_poly_2::StaticBase *b_ptr_s = new inh_poly_2::StaticDerived;
	inh_poly_2::StaticDerived staticderived;
	inh_poly_2::StaticBase &static_base_ref{ staticderived };

	fmt::println("Type of *b_ptr_s : {}", typeid(*b_ptr_s).name());
	fmt::println("Type of static_base_ref : {}", typeid(static_base_ref).name());


	delete b_ptr;
	delete b_ptr_s;
}