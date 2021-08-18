#include <iostream>
#include <vector>
#include <ranges>


int main(){

    //Generate an infinite sequence of numbers
    //auto infinite_view = std::views::iota(1) | std::views::take(20); // Stores the compuation
    //auto data_view = std::views::take( std::views::iota(1) , 20);

    //Numbers are generated lazily, on the fly, as we need them in each iteration
    for(auto i :std::views::iota(1) | std::views::take(20)){
        std::cout << i << std::endl;
    }
    
  
    return 0;
}