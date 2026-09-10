#include <iostream>
#include <vector>


int main(){

    std::vector<int> numbers {1,2,3,4,5,6,7,8,9,10};
    
    //Trying out reverse iterators
    //auto it = numbers.rbegin(); // A reverse iterator increments backwards from the end.
    std::vector<int>::reverse_iterator it= numbers.rbegin();
    *it = 34;
    std::cout << "Numbers : [";
    while(it != numbers.rend()){
        std::cout << " " << *it ;
        ++it;
    }
    std::cout << "] " << std::endl;

    std::cout << "--------" << std::endl;
    /*
    auto it_rev = numbers.rbegin();
    
    if( it_rev != numbers.end()){ // Compiler error.
        std::cout << "Do something..." << std::endl;
    }
    */
   
    return 0;
}