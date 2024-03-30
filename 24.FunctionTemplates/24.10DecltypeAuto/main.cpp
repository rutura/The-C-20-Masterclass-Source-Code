#include <fmt/format.h>

template <typename T, typename P> 
decltype(auto) maximum(T a, P b){
    return (a > b) ? a : b;
}


int main(){
    int x{7};
    double y{45.9};

    auto result = maximum(x,y);
    fmt::println( "max : {}" , result );
    fmt::println( "sizeof(result) : {}" , sizeof(result) );
   
    return 0;
}


