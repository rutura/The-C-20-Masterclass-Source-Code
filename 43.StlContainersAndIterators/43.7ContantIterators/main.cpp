#include <iostream>
#include <vector>


template <typename T>
void print_collection(const T& collection){
    
    auto it = collection.begin();
    
    std::cout << " [";
    while(it != collection.end()){
        std::cout << " " << *it ;
        ++it;
    }
    std::cout << "]" << std::endl;
}


int main(){

    std::vector<int> numbers{ 11,22,33,44,55,66,77};

    std::cout << "numbers : ";
    print_collection(numbers);

    /*
    std::vector<int>::iterator it = numbers.begin();
    while( it != numbers.end()){
        *it = 100;
        ++it;
    }
    */

    std::cout << "numbers : ";
    print_collection(numbers);

    std::cout << "-------" << std::endl;

    //std::vector<int>::const_iterator c_it = numbers.cbegin();
    auto c_it = numbers.cbegin();
    while( c_it != numbers.end()){
       // *c_it = 100;
        ++c_it;
    }


    //Constant reverse iterators
    auto it1 = numbers.crbegin();
    //std::vector<int>::const_reverse_iterator it1= numbers.crbegin();

    while(it1 != numbers.crend()){
      //*it1 = 600; // Compiler error, it1 is a const iterator, we can't modify 
                    // container data through it.
      ++it1;
    }
   
    return 0;
}