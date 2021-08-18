#include <iostream>


int main(){

//Increment/ decrement pointer addresses manually
	
    int scores[10] {11,12,13,14,15,16,17,18,19,20};

    //scores++;
    
    int * p_score { scores};
    
    /*
    std::cout << "Values in scores array (p_score pointer increment) : " << std::endl;
	
    std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	
	std::cout << "Address : " << p_score << " value : " <<  *(p_score) << std::endl;
	++p_score; // Moves froward by sizeof(int) : 4 bytes
	std::cout << std::endl;
    */

   /*
	std::cout << std::endl;
	std::cout << "Explicit addition of integer : " << std::endl;
	p_score = scores; // Reset the pointer to the start of the array
	std::cout << "scores[4] : " << *(p_score + 4) << std::endl; // Moves forward by 4 * sizeof(int)
	*/

    //Can use loops to print these things out : easier
    /*
    p_score = scores;
    
	std::cout << std::endl;
    std::cout << "Pointer arithmetic on p_scores pointer and a for loop: " << std::endl;
    for ( size_t i{0} ; i < std::size(scores) ; ++i){
        std::cout <<"Value : "<< *(p_score + i) << std::endl; // scores[i]
    }
    */


    //Can also do arithmetic on the array name
    //just like any pointer.
    /*
    p_score = scores;
    
	std::cout << std::endl;
    std::cout << "Pointer arithmetic on array name: " << std::endl;
    for ( size_t i{0} ; i < std::size(scores) ; ++i){
        std::cout <<"Value : "<< *(scores + i) << std::endl;
	}
    */

    // Can Print the elements in reverse order
    /*
	std::cout<< std::endl;
    std::cout << "Elements in reverse order with decrementing pointer arithmetic: " << std::endl;
    for ( size_t i{std::size(scores)} ; i > 0 ; --i){
        std::cout <<"Value : "<< *(scores + i -1) << std::endl;	// Here we do the -1 thing, because
																//scores is already pointing to the first
																//element in the array.
    }
    */

	//Print in reverse order with -- operator on p_score
    /*
	std::cout<< std::endl;
    std::cout << "Elements in reverse order -- arithmetic on the p_scores pointer: " << std::endl;
    p_score = scores + std::size(scores) -1;
	for ( size_t i{std::size(scores)} ; i > 0 ; --i){
        std::cout <<"Value : "<< *(p_score--) << std::endl;		// Here we do the -1 thing, because
																//scores is already pointing to the first
																//element in the array.
    }
    */

    // Can Print the elements in reverse order with array index
    /*
	std::cout<< std::endl;
    std::cout << "Elements in reverse order with array index notation: " << std::endl;
    for ( size_t i{std::size(scores)} ; i > 0 ; --i){
        std::cout <<"Value : "<< scores [ i -1] << std::endl;
    }
    */

    p_score = scores;
    
    scores[0] = 31; // Array index notation
    *(scores + 1) = 32; // Equivalent to scores[1] = 32 . Pointer arithmetic on array name
    *(p_score + 2) = 33; // Equivalent to scores[2] = 33 . Pointer arithmetic on p_score pointer
    
	std::cout << std::endl;
	std::cout << "Printing out the array after modification of 3 first elements: " << std::endl;
    for ( size_t i{0} ; i < std::size(scores) ; ++i){
        std::cout <<"Value : "<< scores[i] << std::endl;
    }
	
	
   
    return 0;
}