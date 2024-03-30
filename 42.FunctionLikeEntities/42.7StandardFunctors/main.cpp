#include <fmt/format.h>
#include <functional>
#include "boxcontainer.h"



template <typename T, typename Comparator>
T get_best (const BoxContainer<T>& collection,
                            Comparator comparator){
    T best = collection.get_item(0);
    for(size_t i{}; i < collection.size() ; ++i){
            
        if(comparator(collection.get_item(i),best)){
            best = collection.get_item(i);
        }
    }    
    return best;
}

//Custom function
template <typename T>
bool custom_greater(const T& param1, const T& param2){
     if(param1 > param2){
         return true;
     }
     return false;
}

//Custom functor
template <typename T>
class Greater{
    public : 
    bool operator()(const T& param1, const T& param2){
        return (param1 > param2) ? true : false;
    }
};



int main(){

    std::plus<int> adder;
    std::minus<int> substracter;
    std::greater<int> compare_greater;
    
    fmt::println( " 10 + 7 : {}" , adder(10,7) ); //17
    
    fmt::println( "10 - 7 : {}", substracter(10,7));//3
    
    fmt::println( " 10 > 7 : {}" , compare_greater(10,7) );//true
    
    fmt::println( "---------------------------------" );


    BoxContainer<std::string> quote;
    quote.add("The");
    quote.add("sky");
    quote.add("is");
    quote.add("blue");
    quote.add("my");
    quote.add("friend");
  
    
    std::greater<std::string> string_comparator{};
    
    fmt::println( "quote : {}" , quote );
    //Built in functor
    fmt::println( "greater string : {}" ,get_best(quote,string_comparator) );
    //Custom function pointer
    fmt::println( "greater string : {}" , get_best(quote,custom_greater<std::string>) );
    //Custom functor
    Greater<std::string> greater_string_custom_functor;
    fmt::println( "greater string :{} ", get_best(quote,greater_string_custom_functor) );


    fmt::println( "---------------------------------" );

   BoxContainer<int> ints;
    ints.add(10);
    ints.add(3);
    ints.add(6);
    ints.add(72);
    ints.add(23);
    ints.add(4);
 
    
    std::greater<int> int_comparator{};
    Greater<int> greater_int_custom_functor;
    
    fmt::println( "ints : {}" , ints );
    fmt::println( "greater int :{} ", get_best(ints,int_comparator) );
    fmt::println( "greater int :{} ", get_best(ints , custom_greater<int>) );
    fmt::println( "greater int :{} ", get_best(ints,greater_int_custom_functor) );
    fmt::println( "lesser int : {}" , get_best(ints,std::less<int>{}) );
    
    return 0;
}