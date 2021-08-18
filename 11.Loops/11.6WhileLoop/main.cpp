#include <iostream>

int main(){

	//Print I love C++ 10 times
    /*
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    std::cout << "I love C++" << std::endl;
    */


    const size_t COUNT{100};
    size_t i{0}; // Iterator declaration

    while(i < COUNT ){ // Test
       std::cout << i << " : I love C++" << std::endl;

       ++i; // Incrementation 
    }
    std::cout << "Loop done!" << std::endl;
   
    return 0;
}