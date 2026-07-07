#include <iostream>

int main(){

	const size_t name_length{15};
	
    char members [][name_length] {
        {'J','o','h','n'},
        {'S','a','m','u','e','l',},
        {'R','a','s','h','i','d'},
        {'R','o','d','r','i','g','e','z'}
    };

    //Declaring a 2D array
   
    //Printing out like this is unsafe : may go over and print
	//outside your valid memory block
    //until a terminating null character is encountered.
    /*
	std::cout << "Unsafe printing of members : " << std::endl;
    for (size_t i {0}; i < std::size(members) ; ++i){
        std::cout << members[i] << std::endl;
    }
    */
  


    //Can loop around manually printing out each character
    /*
	std::cout << std::endl;
    std::cout << "Printing out character by character manually : " << std::endl;
    for (size_t i{0} ; i < std::size(members) ; ++i){
        
        for (size_t j{0} ; j < std::size(members[i]) ; ++j){
            
            std::cout << members[i][j] ;
        }
        std::cout << std::endl;
    }
    */
 


	//Better : Using C-string litterals
	//Compared to initialization with charactes with in '', this
	// is even easier to type. The entire string is a single entity 
	//you can manage easily.
    /*
    char members1 [][name_length] {
        "John",
        "Samuel",
        "Rashid",
        "Rodriguez"
    };
    
    //Printing out members1
    std::cout << "Printing out members1 (C-string literals) : " << std::endl;
    for (size_t i {0}; i < std::size(members1) ; ++i){
        std::cout << members1[i] << std::endl;
    }
    */
   


    //Updating our prediction declaration in the fortune teller game
    char predictions [] [90] {
        "a lot of kinds running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before." ,
        "Uhm , I don't see anything!"
        
    };
    
	std::cout << std::endl;
    std::cout << "Prediction : " << predictions[5] << std::endl;
 

   
    return 0;
}