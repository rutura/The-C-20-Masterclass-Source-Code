#include <fmt/format.h>
#include "utility.h"

 inline int age{12};

 inline void some_function(){
	fmt::println( "age : {}" , age );
	fmt::println( "&age : {}" , fmt::ptr(&age ));
}

void print_age_utility1(){
    fmt::println( "Printing from utility1 : " );
    some_function();
    fmt::println( "\n");
}

