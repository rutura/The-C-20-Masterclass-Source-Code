#include <fmt/format.h>

//No linkage
void some_function(){
    int age {34}; // No linkage
    fmt::println( "age : {}{}{}" , age , " &age : " , fmt::ptr(&age ));
}

const double distance{45.8}; // Internal linkage

int item_count {6}; // External linkage



extern void print_distance();
extern void print_item_count();

int main(){

/*
    fmt::println( "distance(main) : {}{}{}" , distance , "  &distance : " , fmt::ptr(&distance) );

    fmt::println( "-----" );

    print_distance();
*/


    fmt::println( "item_count(main) : {}{}{}" , item_count , " &item_count : "
        , fmt::ptr(&item_count ));

    fmt::println( "-----" );
    print_item_count();

   
    
    return 0;
}