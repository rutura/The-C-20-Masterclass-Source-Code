#include <fmt/format.h>

int main(){


    for(double multiplier{4}; auto i : {1,2,3,4,5,6,7,8,9,10}){
        fmt::println("result : {}", ( i * multiplier) );
    }

   
    return 0;
}