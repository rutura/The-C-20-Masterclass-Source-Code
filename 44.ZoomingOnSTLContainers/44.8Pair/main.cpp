#include <fmt/format.h>
#include <vector>
#include <utility>


int main(){

    //Code1 : Create pair
    fmt::println( "creating pairs:" );
    std::pair<int,std::string> pair1{0,"Book shelf"};
    
    auto pair2 = std::make_pair(1,"Table"); // Deduces the template arguments

    //fmt::println( "pair1 : " << pair1 );

    fmt::println( " pair1 : ({},{})",  pair1.first,  pair1.second );
    fmt::println( " pair2 : ({},{})",  pair2.first, pair2.second  );

    //Code2 : auto[] syntax - collect components of a pair into variables.
    fmt::println("");
    fmt::println( "auto[] syntax - collect components of a pair into variables : " );
    auto [int_var, string_var] = pair1;
    fmt::println( "pair1 (auto[] syntax) : ({},{})" , int_var,  string_var );
    
    

    //Code3 : template argument deduction (C++17)
    fmt::println("");
    fmt::println( "template argument deduction : " );
    
    std::pair student(33165, std::string("John Snow"));// Deducing the template arguments
    
    fmt::println( "student ID : {}", student.first );
    fmt::println( "Student name : {}", student.second );


    //Code4 : collection of pairs
    fmt::println("");
    fmt::println( "collection of pairs : " );
    
    std::vector<std::pair<int,std::string>> collection {{10,"Earth"},{20,"Spins"},
                                                        {30,"From"},{40,"Left"},
                                                        {50,"To"},{60,"Right"}};
    //Traverse : syntax1
    fmt::println("");
    fmt::println( "syntax1 : " );
    fmt::print( "collection : [");
    for(const auto& elt : collection){
        fmt::print( " ({},{})",  elt.first , elt.second);
    }
    fmt::println( "]" );


    //Traverse : syntax2
    fmt::println("");
    fmt::println( "syntax2 : " );
    fmt::print( "collection : [");
    for( auto[key,value] : collection){
        fmt::print( " ({},{})",  key , value);
    }
    fmt::println( "]" );
   
    return 0;
}