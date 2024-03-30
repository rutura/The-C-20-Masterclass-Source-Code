#include "adder.h"


int main(){

    Adder<int> adder_int;
	adder_int.do_something();
    fmt::println( "{}", adder_int.add(10,20) );

    fmt::println( "-------" );

    //Char*
    char str1[20] {"Hello"};
    char str2[] {" World!"};
    
    Adder<char*> adder_c_str;
	//adder_c_str.do_something();
    fmt::println( "{}", adder_c_str.add(str1,str2) );
   
    return 0;
}