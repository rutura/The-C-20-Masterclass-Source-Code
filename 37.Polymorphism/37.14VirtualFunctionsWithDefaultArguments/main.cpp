#include <fmt/format.h>
#include "derived.h"

int main(){

    //Base ptr : Uses polymorphism
    Base * base_ptr1 = new Derived;
    double result = base_ptr1->add();
    fmt::println("Result (base ptr) : {}" , result  ); //12


    fmt::println( "---------------------");
	
    //Base ref : Uses Polymorphism
    Derived derived1;
    Base& base_ref1 = derived1;
    result = base_ref1.add();
    fmt::println( "Result (base ref) : {}" , result ); // 12
    
    fmt::println( "---------------------");


    //Raw objects
    Base base3;
    result = base3.add();
    fmt::println( "raw result : {}" , result );

    fmt::println( "---------------------");

    //Direct object : Uses static binding
    Derived derived2;
    result = derived2.add();
    fmt::println( "Result (Direct object) : {}" , result ); // 22
	
    fmt::println( "---------------------");

	//Raw objects - slicing : uses static binding
	Base base1 = derived2;
	result = base1.add();
    fmt::println( "Result (Raw objects assignment) : {}" , result ); //11

   
    return 0;
}