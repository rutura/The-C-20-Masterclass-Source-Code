#include <fmt/format.h>

int main(){

    //Capture lists
    /*
     double a{10};
     double b{20};
     
     auto func = [a,b](){
         fmt::println( "a + b : " , a + b );
     };
     func();

    //Capturing by value
     int c{42};

     auto func = [c](){
         fmt::println( "Inner value : {}{}{}" , c , " &inner : " ,fmt::ptr(&c ));
     };
     
     for(size_t i{} ; i < 5 ;++i){
         fmt::println( "Outer value : {}{}{}" , c , " &outer : " , fmt::ptr(&c ));
         func();
         ++c;
     };
     */

    //Capture by reference
     int c{42};

     auto func = [&c](){
         fmt::println( "Inner value : {} {}{}" , c , " &inner : " ,fmt::ptr(&c ));
     };
     
     for(size_t i{} ; i < 5 ;++i){
         fmt::println( "Outer value : {} {}{}" , c , " &outer : " , fmt::ptr(&c ));
         func();
         ++c;
     }
    
    return 0;
}