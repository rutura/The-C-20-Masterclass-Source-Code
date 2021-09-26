#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>
#include "boxcontainer.h"


template <typename T>
void print(const BoxContainer<T>&  c){
    for(auto i : c){ // Computation happens here.
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(){

    BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(7);
    vi.add(2);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);

    const BoxContainer<int> copy(vi);

    //Printing a const container
    std::cout << "data : ";
    for (auto it = copy.begin(); it!=copy.end(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;

    //Printing throgh a function
    std::cout << "copy : ";
    print(copy);


    //Attempt to sort copy
    //std::ranges::sort(copy); // Compiler error. Can't sort a const collection
    std::ranges::sort(vi);

    std::cout << "vi : ";
    print(vi);


    std::cout << "view taking only 3 : " ;
    for(auto i : std::views::take(vi,3)){
        std::cout << i << " " ;
    }
    std::cout << std::endl;
    
    std::cout << "End!" << std::endl;

   


   
 
    return 0;
}