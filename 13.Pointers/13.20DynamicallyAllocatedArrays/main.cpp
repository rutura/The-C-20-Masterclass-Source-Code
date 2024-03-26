#include <fmt/format.h>

int main(){

    const size_t size{10};
    
    //Different ways you can declare an array
	//dynamically and how they are initialized
	
    double *p_salaries { new double[size]}; // salaries array will
															//contain garbage  values
    int *p_students { new(std::nothrow) int[size]{} }; // All values initialized to 0 
    
    double *p_scores { new(std::nothrow) double[size]{1,2,3,4,5}}; // Allocating memory space
																	// for an array  of size double
																	//vars. First 5 will be initialized
																	//with 1,2,3,4,5, and the 
																	//rest will be 0's.


    //nullptr check and use the allocated array
    if(p_scores){
        fmt::println( "size of scores (it's a regular pointer) : {}" , sizeof(p_scores) );
        fmt::println( "Successfully allocated memory for scores.");
        
        //Print out elements. Can use regular array access notation, or pointer arithmetic
        for( size_t i{}; i < size ; ++i){
           fmt::println( "value : {}: {}" , p_scores[i] , *(p_scores + i) );
        }
    }

    delete [] p_salaries;
    p_salaries = nullptr;

    delete [] p_students;
    p_students = nullptr;

   delete [] p_scores;
   p_scores = nullptr;

   //Static arrays Vs dynamic arrays
   fmt::println( "=====================================" );

   int scores[10] {1,2,3,4,5,6,7,8,9,10}; // Lives on the stack

   fmt::println( "scores size : {}" , std::size(scores) );
   for( auto s : scores){
       fmt::println( "value : {}" , s );
   }

   int* p_scores1 = new int[10] {1,2,3,4,5,6,7,8,9,10}; // Lives on the heap.
   //fmt::println( "p_scores1 size : {}" , std::size(p_scores) );
   /*
   for( auto s : p_scores1){
       fmt::print( "value : " , s );
   }
   */


   
    return 0;
}