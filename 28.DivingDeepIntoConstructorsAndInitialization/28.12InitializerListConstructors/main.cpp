#include <fmt/format.h>
#include <cassert>

struct Point{
public: 
    Point( std::initializer_list<double> list){
        //static_assert( (list.size() == 2));
        assert(list.size() == 2); // If the size of the list is not 2, terminate the program with an error
        /*
        fmt::println("Initalizer list constructor called" );
        fmt::println("list size : {}" , list.size() );
        
        for(size_t i{} ;  i < list.size(); ++i){
            fmt::println("elt [{}{}{}" , i , "]  :" , *(list.begin() + i) );
        }
         */
       x = *(list.begin());
       y = *(list.begin() + 1);
    }

    void print_point() const {
        fmt::println( "Point [ x : {}{}{}{}" , x , ", y : " , y , "]" );
    }
 private : 
    double x;
    double y;
};



int main(){

    Point p1{22.4,34.9};
    p1.print_point();
   
   
    return 0;
}