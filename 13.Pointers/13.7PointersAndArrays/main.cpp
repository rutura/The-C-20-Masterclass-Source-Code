#include <fmt/format.h>


int main(){

	int scores[10] {11,12,13,14,15,16,17,18,19,20};
    
    int * p_score { scores};
    
    //Print the address
    fmt::println( "scores : {}" , fmt::ptr(scores) ); // Array
    fmt::println( "p_score : {}" , fmt::ptr(p_score) );// Pointer
    fmt::println( "&scores[0]  :{} " , fmt::ptr(&scores[0]) );
    
    //Print the content at that address
	fmt::println( "Printing out data at array address : " );
    fmt::println( "*scores : {}" , *scores );
    fmt::println( "scores[0] : {}" , scores[0] );
    fmt::println( "*p_score : {}" , *p_score );
	fmt::println( "p_score[0] : {}" , p_score[0] );


    //Differences
    int number {21};
    p_score = &number;
    
    //scores = &number; // The array name is a pointer, but a special pointer that kind of identifies
                       // the entire array. You'll get the error  : incompatible types in assignment
                      // of 'int*' to 'int[10]'
    
    fmt::println( "p_score : {}" , fmt::ptr(p_score) );// Pointer

	//std::size() doesn't work for raw pointers
	fmt::println( "size : {}" , std::size(scores) );
	//fmt::println( "size : {}" , std::size(p_score) ); // Compiler error.
   
    return 0;
}