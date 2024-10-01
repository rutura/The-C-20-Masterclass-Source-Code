module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import virtual_destructors;
import dynamic_casts;
import poly_func_and_destructors;
import typeid_operator;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void virtual_destructors_demo(){
	
	virtual_destructors::Animal *p_animal = new virtual_destructors::Dog();

	delete p_animal;
}


//For use with dynamic casts
void do_something_with_animal_ptr(dynamic_casts::Animal *animal)
{
  fmt::println("In function taking base pointer...");
  dynamic_casts::Feline *feline_ptr = dynamic_cast<dynamic_casts::Feline *>(animal);

  if (feline_ptr) {
    feline_ptr->do_some_feline_thingy();
  } else {
    fmt::println("Couldn't cast to Feline pointer,Sorry.");
  }
}

void do_something_with_animal_ref(dynamic_casts::Animal &animal)
{
  fmt::println("In function taking base reference...");
  dynamic_casts::Feline *feline_ptr_1{ dynamic_cast<dynamic_casts::Feline *>(&animal) };
  if (feline_ptr_1) {
    feline_ptr_1->do_some_feline_thingy();
  } else {
    fmt::println("Couldn't cast to Feline reference,Sorry.");
  }
}


export void dynamic_casts_demo(){

	// Base class pointer
	dynamic_casts::Animal *animal1 = new dynamic_casts::Feline("stripes", "feline1");
	// animal1->do_some_feline_thingy();


	fmt::println("-----------");

	// If the cast succeeds, we get a valid pointer back,
	// if it fails, we get nullptr. So we can check before
	// calling stuff on the returned pointer
	dynamic_casts::Feline *feline_ptr = dynamic_cast<dynamic_casts::Feline *>(animal1);

	if (feline_ptr) {
		feline_ptr->do_some_feline_thingy();
	} else {
		fmt::println("Couldn't do the transformation from Animal* to Dog*");
	}

	fmt::println("-----------");

	// Can do the transformation downstream for references

	// Base class reference
	dynamic_casts::Feline feline2("stripes", "feline2");
	dynamic_casts::Animal &animal_ref = feline2;

	// Calling non virtual methods on animal_ref won't work
	// animal_ref.do_some_feline_thingy();

	// Dog & feline_ref {dynamic_cast<Dog&>(animal_ref)};
	// feline_ref.do_some_dog_thingy();


	// Doing proper checks with references
	dynamic_casts::Dog *feline_ptr_1{ dynamic_cast<dynamic_casts::Dog *>(&animal_ref) };
	if (feline_ptr_1) {
		feline_ptr_1->do_some_dog_thingy();
	} else {
		fmt::println("Couldn't cast to Dog reference,Sorry.");
	}


	fmt::println("---------------");
	do_something_with_animal_ptr(animal1);
	do_something_with_animal_ref(animal_ref);


	fmt::println("----------------");
	/*
	int data{45};
	int data_ptr = &data;

	std::string data_str = dynamic_cast<std::string *>(data_ptr);
	*/

	fmt::println("Done!");

	delete animal1;	
}


export void poly_func_and_destructors_demo(){
	poly_func_and_destructors::Base *p_base = new poly_func_and_destructors::Derived;

	p_base->setup();

	auto value = p_base->get_value();
	fmt::println("value : {}", value);// 100

	p_base->clean_up();

	delete p_base;
}


export void typeid_operator_demo(){

	// 1. typeid with fundemental types : returns static type
	fmt::println("typeid(int) : {}", typeid(int).name());
	if (typeid(22.2f) == typeid(float)) {
		fmt::println("22.2f is a float");
	} else {
		fmt::println("22.2f is not float");
	}

	fmt::println("----------------");
	// 2. typeid with references(polymorphic)
	fmt::println("Polymorphic references : ");
	typeid_operator::DynamicDerived dynamic_derived;
	typeid_operator::DynamicBase &base_ref = dynamic_derived;
	fmt::println("Type of dynamic_derived : {}", typeid(dynamic_derived).name());
	fmt::println("Type of base_ref : {}", typeid(base_ref).name());

	fmt::println("----------------");

	// 3. typeid with pointers(polymorphic)
	fmt::println("Polymorphic pointers : ");
	typeid_operator::DynamicBase *b_ptr = new typeid_operator::DynamicDerived;

	fmt::println("Type of b_ptr : {}", typeid(b_ptr).name());// static type

	// ATTENTION :
	//			 For pointers you have to dereference to see the dynamic type //
	fmt::println("Type of *b_ptr : {}", typeid(*b_ptr).name());


	fmt::println("----------------");

	// 4. type id with non polymorphic pointers and refs : We'll get static types
	// because we're using static binding, the default behavior
	fmt::println("Non polymorphic pointers and refs : ");
	typeid_operator::StaticBase *b_ptr_s = new typeid_operator::StaticDerived;
	typeid_operator::StaticDerived staticderived;
	typeid_operator::StaticBase &static_base_ref{ staticderived };

	fmt::println("Type of *b_ptr_s : {}", typeid(*b_ptr_s).name());
	fmt::println("Type of static_base_ref : {}", typeid(static_base_ref).name());


	delete b_ptr;
	delete b_ptr_s;
}