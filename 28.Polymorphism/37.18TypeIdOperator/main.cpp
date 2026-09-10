#include <iostream>
#include "polymorphic.h"
#include "nonpolymorphic.h"


int main(){

	//1. typeid with fundemental types : returns static type
    std::cout << "typeid(int) : " << typeid(int).name() << std::endl;
	if(typeid(22.2f) == typeid(float)){
		std::cout << "22.2f is a float" << std::endl;
	}else{
		std::cout << "22.2f is not float" << std::endl;
	}

	std::cout << "----------------" << std::endl;
	//2. typeid with references(polymorphic)
	std::cout << "Polymorphic references : " << std::endl;
	DynamicDerived dynamic_derived;
	DynamicBase& base_ref = dynamic_derived;
	std::cout << "Type of dynamic_derived : " << typeid(dynamic_derived).name() << std::endl;
	std::cout << "Type of base_ref : " << typeid(base_ref).name() << std::endl;


	std::cout << "----------------" << std::endl;

	//3. typeid with pointers(polymorphic)
	std::cout << "Polymorphic pointers : " << std::endl;
	DynamicBase * b_ptr = new DynamicDerived;
  
	std::cout << "Type of b_ptr : " << typeid(b_ptr).name() << std::endl; // static type
	
	//ATTENTION :
	//			 For pointers you have to dereference to see the dynamic type //
	std::cout << "Type of *b_ptr : " << typeid(*b_ptr).name() << std::endl;


	std::cout << "----------------" << std::endl;

	//4. type id with non polymorphic pointers and refs : We'll get static types
	//because we're using static binding, the default behavior
	std::cout << "Non polymorphic pointers and refs : " << std::endl;
	StaticBase * b_ptr_s = new StaticDerived;
	StaticDerived staticderived;
	StaticBase& static_base_ref {staticderived};
  
	std::cout << "Type of *b_ptr_s : " << typeid(*b_ptr_s).name() << std::endl;
	std::cout << "Type of static_base_ref : " << typeid(static_base_ref).name() << std::endl;
  

    delete b_ptr;
    delete b_ptr_s;
	

    return 0;
}