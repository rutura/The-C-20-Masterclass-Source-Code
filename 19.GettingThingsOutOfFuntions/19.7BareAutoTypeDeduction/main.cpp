#include <fmt/format.h>


int main(){

    //Type deduction with auto : Just a copy
	/*
	double some_var{55.5};
	
	auto x = some_var;
	
	fmt::println( "sizeof(some_var) : {}" , sizeof(some_var) );
	fmt::println( "sizeof(x) : {}" , sizeof(x) );
	fmt::println( "&some_var : {}" , fmt::ptr(&some_var) );
	fmt::println( "&x : {}" , fmt::ptr(&x) );
    fmt::println( " some_var : {}" , some_var );
    fmt::println( " x : {}" , x );
    */



	/*
	double some_var = 55.5; //double
	
	double& some_var_ref {some_var};
	
	auto y = some_var_ref; // y is not deduced as a reference to double
						   // it's just a double that contains the value 
						   // in some_var_ref
	++y;
					
	fmt::println( "sizeof(some_var) : {}" , sizeof(some_var) ); // 8
	fmt::println( "sizeof(some_var_ref) : {}" , sizeof(some_var_ref) ); // 8
	fmt::println( "sizeof(y) : {}" , sizeof(y) ); // 8
	fmt::println( "&some_var : {}" , fmt::ptr(&some_var) ); // 0xabc123
	fmt::println( "&some_var_ref : {}" , fmt::ptr(&some_var_ref) ) ;// 0xabc123
	fmt::println( "&y : {}" , fmt::ptr(&y) );  // 0xaab543
	fmt::println( "some_var : {}" , some_var ); //55.5
	fmt::println( "some_var_ref : {}" , some_var_ref ); // 55.5
	fmt::println( "y : {}" , y ); // 56.5
	*/


   // True reference deduction
   	/*
   	double some_var = 55.5; //double
    double& some_var_ref {some_var};

	
	auto& z = some_var_ref; // z is deduced as a double reference
	++z;
	
	fmt::println( "sizeof(some_var) : {}" , sizeof(some_var) ); // 8
	fmt::println( "sizeof(some_var_ref) : {}" , sizeof(some_var_ref) ); // 8
	fmt::println( "sizeof(z) : {}" , sizeof(z) ); // 8
	fmt::println( "&some_var : {}" , fmt::ptr(&some_var) );// 0xabc123
	fmt::println( "&some_var_ref : {}" , fmt::ptr(&some_var_ref) );// 0xabc123
	fmt::println( "&z : {}" , fmt::ptr(&z) );// 0xabc123
	fmt::println( "some_var : {}" , some_var ); // 56.5
	fmt::println( "some_var_ref : {}" , some_var_ref ); //56.5
	fmt::println( "z : {}" , z ); // 56.5
	*/


	//Constness is preserved with properly deduced references.
    /*
	const double some_other_var {44.3};
	
	const double& const_ref {some_other_var};
	
	auto& p = const_ref;
	
	fmt::println( "some_other_var : {}" , some_other_var );
	fmt::println( "const_ref : {}" , const_ref );
	fmt::println(  "p : {}" , p );
	
	//++p; // Compiler error
	
	fmt::println( "some_other_var : {}" , some_other_var );
	fmt::println( "const_ref : {}" , const_ref );
	fmt::println(  "p : {}" , p );
    */

	//Constness doesn't matter with non reference deduction
	const double i_am_const {71.2};
    const double& my_ref {i_am_const};

	auto q = my_ref; // q is a separate variable, initialized with the
							// value in i_am_const.
	++q;// Can modify q without a problem. It's a copy.
	




	
   
    return 0;
}