#include <fmt/format.h>


template <typename ReturnType = double , typename T, typename P>
ReturnType maximum ( T a, P b){
    return (a > b) ? a : b;
}

template < typename T, typename P,typename ReturnType = double>
ReturnType minimum ( T a, P b){
    return (a < b) ? a : b;
}

int main(){

    double a{6};
    double b{9.5};

    auto result = minimum <int,double,int> (a,b);
    fmt::println( "result : {}" , result );
    fmt::println( "sizeof(result) : {}" , sizeof(result) );//4
   
    return 0;
}