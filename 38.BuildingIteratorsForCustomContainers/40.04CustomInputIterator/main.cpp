#include <iostream>
#include <algorithm>
#include <vector>
#include "boxcontainer.h"

template <typename T>
std::ostream& operator<<( std::ostream& out,const  std::vector<T>& vec){
    out << " [ ";
    for(auto i : vec){
        out << i  << " ";
    }
    out << "]";
    return out;
}


int main(){

    //std::vector<int> box1 {8,1,4,2,5,3,7,9};
    BoxContainer<int> box1;
    box1.add(5);
    box1.add(1);
    box1.add(4);
    box1.add(8);
    box1.add(5);
    box1.add(3);
    box1.add(7);
    box1.add(9);
    box1.add(6);
   

    std::cout << "box : " << box1 << std::endl;

    //find algorithm
    if (std::ranges::find(box1, 8) != box1.end()) {
        std::cout << "numbers contains: " << 8 << std::endl;
    } else {
        std::cout << "numbers does not contain: " << 8 << std::endl;
    }


    //std::ranges::reverse(box1.begin(),box1.end());


    //Range based for loop
    /*
    for(auto n : box1){
        std::cout << n << " ";
    }
    std::cout << std::endl;
    */
   
    return 0;
}