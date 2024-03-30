#include <fmt/format.h>
#include <algorithm>
#include <set>
#include <list>


int main(){

    //std::vector<int> v {3,400,51,6,7,23,56,71};
    //int v[] {3,400,51,6,7,1123,56,71};
    std::list<int> v {3,400,51,6,7,23,56,71};

    //max_elt and min_elt return an iterator to the found elt
    auto result = std::max_element(std::begin(v), std::end(v));
    fmt::println( "max element is : {}" , *result );
    
    result = std::min_element(std::begin(v),std::end(v));
    fmt::println( "min element is : {}" , *result );


    fmt::println( "----------" );

    //Distances : closest and furthest
    int number_to_find {100};
    
    auto distance = [number_to_find](int x, int y){
        return (std::abs(x-number_to_find) < std::abs(y-number_to_find));
    };
    
    //Finding the closest
    result = std::min_element(std::begin(v),std::end(v),distance);
    fmt::println("{} is closest to {}" , *result, number_to_find );
    
    //Finding the furthest
    result = std::max_element(std::begin(v),std::end(v),distance);
    fmt::println( "{} is furthest from  {}", *result, number_to_find );


    fmt::println( "--------------------------------" );

    //Capturing min and max in a pair object with the auto syntax
    const auto[near,far] = std::minmax_element(std::begin(v),std::end(v),distance);
    fmt::println("{} is closest to {}" ,  *near, number_to_find );
    fmt::println(  "{} is furthest from  {}" ,*far,  number_to_find );
    
    return 0;
}