#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void print_collection( const T& collection){
    
    std::cout << " Collection [" ;
    for(const auto& elt : collection){
        std::cout << " " << elt ;
    }
    std::cout << "]" << std::endl;
}


int main(){

    //Original collection
    std::vector<int> input = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3,11,45,6,23}; 
    std::vector<int> output{11,22,33};
    std::cout << "output size : " << output.size() << std::endl;
    std::cout << "output capacity : " << output.capacity() << std::endl;

    print_collection(input);
    print_collection(output);

    //Uses whatever space is there, doesn't extend the capacity
    //std::transform(input.begin(),input.end(),output.begin(),[](int n){return n*2;});

    //std::back_inserter_iterator : appends to the back, extends capacity if necessary.
    std::transform(input.begin(),input.end(),std::back_inserter(output),[](int n){return n*2;});

    print_collection(output);
    std::cout << "output size : " << output.size() << std::endl;
    std::cout << "output capacity : " << output.capacity() << std::endl;


    std::cout << "Done!" << std::endl;
    
    return 0;
}