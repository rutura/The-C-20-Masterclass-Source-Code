#include <fmt/format.h>
#include "polymorphic.h"
#include "nonpolymorphic.h"


int main(){

	//1. typeid with fundemental types : returns static type
    fmt::println( "typeid(int) : {}" , typeid(int).name() );
	if(typeid(22.2f) == typeid(float)){
		fmt::println( "22.2f is a float" );
	}else{
		fmt::println( "22.2f is not float" );
	}

	fmt::println( "----------------" );
	//2. typeid with references(polymorphic)
	fmt::println( "Polymorphic references : " );
	DynamicDerived dynamic_derived;
	DynamicBase& base_ref = dynamic_derived;
	fmt::println( "Type of dynamic_derived : {}" , typeid(dynamic_derived).name() );
	fmt::println( "Type of base_ref : {}" , typeid(base_ref).name() );


	fmt::println( "----------------" );

	//3. typeid with pointers(polymorphic)
	fmt::println( "Polymorphic pointers : " );
	DynamicBase * b_ptr = new DynamicDerived;
  
	fmt::println( "Type of b_ptr : {}" , typeid(b_ptr).name() ); // static type
	
	//ATTENTION :
	//			 For pointers you have to dereference to see the dynamic type //
	fmt::println( "Type of *b_ptr : {}" , typeid(*b_ptr).name() );


	fmt::println( "----------------" );

	//4. type id with non polymorphic pointers and refs : We'll get static types
	//because we're using static binding, the default behavior
	fmt::println( "Non polymorphic pointers and refs : " );
	StaticBase * b_ptr_s = new StaticDerived;
	StaticDerived staticderived;
	StaticBase& static_base_ref {staticderived};
  
	fmt::println( "Type of *b_ptr_s : {}" , typeid(*b_ptr_s).name() );
	fmt::println( "Type of static_base_ref : {}" , typeid(static_base_ref).name() );
  

    delete b_ptr;
    delete b_ptr_s;
	

    return 0;
}