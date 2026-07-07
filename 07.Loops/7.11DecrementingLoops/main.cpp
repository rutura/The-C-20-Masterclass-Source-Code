#include <iostream>

int main(){

    const size_t COUNT {5};

    /*
    // For loops
	
	
	std::cout << "Incrementing for loop : " << std::endl;
    for (size_t i{} ; i < COUNT ; ++i){
        std::cout << "i  : " << i << std::endl;
    }
	
	
	std::cout << std::endl;
	std::cout << "Decrementing for loop : " << std::endl;
	
    for(size_t i{COUNT} ; i > 0 ; --i){
        std::cout << "i : " << i << std::endl;
    }
    */

    //Range based for loops can't be made to run in reverse order


    //While loop
    /*
    //Incrementing while
	std::cout << std::endl;
	std::cout << "Incrementing while" << std::endl;
	
    size_t i{0};
    
    while( i < COUNT){
        std::cout << "i : " << i << std::endl;
        ++i;
    }
    
    //Decrementing while
	std::cout << std::endl;
	std::cout << "Decrementing while : " << std::endl;
    i = COUNT;
    
    while( i > 0){
        std::cout << "i : " << i << std::endl;
        --i;
    }
    */

   //Do while loop
    /*
	//Incrementing do while
    std::cout << std::endl;
	std::cout << "Incrementing do while" << std::endl;
    size_t i = 0;
    
    do {
        std::cout << "i : " << i << std::endl;
        ++i;
        
    }while ( i < COUNT);
    
    
    //Decrementing do while
	std::cout << std::endl;
	std::cout << "Decrementing do while" << std::endl;
    i = COUNT;
    
    do {
        std::cout << "i : " << i << std::endl;
        --i;
    }while ( i > 0);
    */


   //Infinite loop
    //Decrementing do while
	std::cout << std::endl;
	std::cout << "Decrementing do while" << std::endl;
    unsigned int i = COUNT;
    
    do {
        std::cout << "i : " << i << std::endl;
        --i;
    }while ( i >= 0);

    return 0;
}