#include <fmt/format.h>

int main(){

    int bag_of_values [] {1,2,3,4,5,6,7,8,9,10}; // This is a collection of integers
    // The variable value will be assigned a value from the values array on each iteration
	
    /*
    for(size_t i {0} ; i < 10 ; ++i){
        fmt::println( "value : {}" , bag_of_values[i] );
    }
    */
	

    /*
    for (int value : bag_of_values){
        //value holds a copy of the current iteration in the whole bag
        fmt::println( " value : {}" , value );
    }
    */


   //Specify the collection in place
   /*
    for (int value : {1,2,3,4,5,6,7,8,9,10}){
        //value holds a copy of the current iteration in the whole bag
        fmt::println( " value : {}" , value );
    }
    */

   //Auto type deduction
	for (auto value : {1,2,3,4,5,6,7,8,9,10}){
        //value holds a copy of the current iteration in the whole bag
        fmt::println( " value : {}" , value );
    }
   
    return 0;
}