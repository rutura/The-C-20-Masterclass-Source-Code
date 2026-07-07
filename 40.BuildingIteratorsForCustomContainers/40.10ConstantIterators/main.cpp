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

    std::cout << "data : ";
    for (auto it = copy.begin(); it!=copy.end(); ++it){
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;


    //print(copy);


   
 
    return 0;
}