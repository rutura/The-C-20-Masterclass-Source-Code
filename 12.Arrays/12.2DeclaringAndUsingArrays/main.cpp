#include <fmt/format.h>

int main(){

    //Declare an array of ints
   // int scores [10]; // Junk data

    //Read data

   // fmt::println( " scores [0] : {}",  scores[0] );
   // fmt::println( " scores [1] : {}",  scores[1] );
   

    //Read with a loop
    /*
    for( size_t i {0} ; i < 10 ; ++i){
        fmt::println("scores [{}] : {}", i, scores[i] );
    }
    */
  


   /*
    scores[0] = 20;
    scores[1] = 21;
    scores[2] = 22;

    //Print the data out
    for( size_t i {0} ; i < 10 ; ++i){
	fmt::println("scores [{}] : {}", i, scores[i] );

    }
    */


   //Write data in a loop
   /*
   for(size_t i{0}; i < 10 ; ++i){
       scores[i] = i * 10;
   }

    //Print the data out
    for( size_t i {0} ; i < 10 ; ++i){
	fmt::println("scores [{}] : {}", i, scores[i] );


    }
    */

    //Declare and initialize at the same time
    /*
	double salaries[5] {12.7, 7.5, 13.2, 8.1, 9.3};
	
	for(size_t i{0}; i < 5; ++i){
        fmt::println("salaries [{}] : {}", i, salaries[i] );
;
	}
    */
  

    //If you don't initialize all the elements, those you leave out
    //are initialized to 0
    /*
    int families[5] {12, 7, 5};
	
	for(size_t i{0}; i < 5; ++i){
	fmt::println("families [{}] : {}", i, families[i] );

	}
    */
    

   	//Omit the size of the array at declaration
   /*
    int class_sizes[] {10,12,15,11,18,17,23,56}; 
	
	// Will print this with a range based for loop
	for(auto value : class_sizes){
		fmt::println("value : {}", value);
	}
    */
    


   // Read only arrays
   /*
   const int birds[] {10,12,15,11,18,17,23,56}; 
   birds[2] = 8;
   */


    //Sum up scores array, store result in sum
 
    int scores [] {2,5,8,2,5,6,9};
    int sum {0};
    
    for( int element : scores){
        sum += element;
    }
    fmt::println("Score sum : {}", sum );
  
   
    return 0;
}