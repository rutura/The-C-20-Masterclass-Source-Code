#include <fmt/format.h>

 inline int age{12};

 inline void some_function(){
	fmt::println( "age : " , age );
	fmt::println( "&age : " ,fmt::ptr( &age ));
}

void print_age_utility2(){
    fmt::println( "Printing from utility2 : " );
    some_function();
    fmt::println( "\n");
}


