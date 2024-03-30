#include <fmt/format.h>
#include <ranges>
#include <concepts>
#include <list>
#include <vector>
#include <algorithm>

template<typename T>
void print_collection( const T& collection){
    
    fmt::print( " Collection [") ;
    for(const auto& elt : collection){
        fmt::print( " {}", elt );
    }
    fmt::print( "]");
}



int main(){

	std::vector<int> numbers {11,2,6,4,8,3,17,9};
    print_collection(numbers);

    //std::ranges::all_of()
    fmt::println("");
    fmt::println( "std::ranges::all_of() : " );

    auto odd = [](int n){
        return n%2 !=0;
    };
    
    //Ranges, iterator pair
    auto result = std::ranges::all_of(numbers.begin(),numbers.end(),odd);

    if(result){
        fmt::println( "All elements in numbers are odd" );
    }else{
        fmt::println( "Not all elements in numbers are odd" );
    }



    //For each
    fmt::println("");
    fmt::println( "std::ranges::for_each() : " );
    print_collection(numbers);
    std::ranges::for_each(numbers.begin(),numbers.end(),[](int& n){n*=2;});
    print_collection(numbers);

 
    //Sort
    fmt::println("");
    fmt::println( "std::ranges::sort() : " );
    print_collection(numbers);
    std::ranges::sort(numbers.begin(),numbers.end());
    print_collection(numbers);

    //Find
    fmt::println("");
    fmt::println( "std::ranges::find() : " );
    auto odd_n_position = std::ranges::find_if(numbers.begin(),numbers.end(),odd);
    
    if (odd_n_position != std::end(numbers)) {
        fmt::println( "numbers contains at least one odd number : {}" , *odd_n_position  );
    } else {
        fmt::println( "numbers does not contain any odd number" );
    }

    //Copy to the output stream
    fmt::println("");
    fmt::print( "numbers : ") ;
    // std::ranges::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(std::cout, " "));
    fmt::print("{}\n", fmt::join(numbers | std::views::common, " "));

  
    //Why you should prefer std::ranges algorithms from now on
    fmt::println("");
    std::vector<int> numbers_list {11,2,6,4,8,3,17,9};
    fmt::print( "numbers_list : ");
    print_collection(numbers_list);

    std::ranges::sort(numbers_list.begin(),numbers_list.end());
  



    return 0;
}