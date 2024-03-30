#include <fmt/format.h>
#include <algorithm>
#include <vector>

template<typename T>
void print_collection( const T& collection){
    
    fmt::print( " Collection [" );
    for(const auto& elt : collection){
        fmt::print( " {}", elt) ;
    }
    fmt::println( "]");
}


int main(){

    //Original collection
    std::vector<int> input = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3,11,45,6,23}; 
    std::vector<int> output{11,22,33};
    fmt::println( "output size : {}" , output.size() );
    fmt::println( "output capacity : {}" , output.capacity() );

    print_collection(input);
    print_collection(output);

    //Uses whatever space is there, doesn't extend the capacity
    //std::transform(input.begin(),input.end(),output.begin(),[](int n){return n*2;});

    //std::back_inserter_iterator : appends to the back, extends capacity if necessary.
    std::transform(input.begin(),input.end(),std::back_inserter(output),[](int n){return n*2;});

    print_collection(output);
    fmt::println( "output size : {}" , output.size() );
    fmt::println( "output capacity : {}" , output.capacity() );


    fmt::println( "Done!" );
    
    return 0;
}