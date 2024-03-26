#include <fmt/format.h>

//Global namespace
double add(double a, double b){
    return a + b;
}

namespace My_Thing{
    double add(double a, double b){
        return a + b - 1;
    }
    
    void do_something(){
        double result = ::add(5,6);
        fmt::println( "result : {}" , result );
    }
    
}


int main(){
    My_Thing::do_something();
  
    return 0;
}