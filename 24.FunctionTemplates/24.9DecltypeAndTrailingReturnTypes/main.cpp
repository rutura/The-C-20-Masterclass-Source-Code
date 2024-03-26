#include <fmt/format.h>

//Declaration
template <typename T, typename P>
auto maximum( T a, P b) -> decltype((a > b)? a : b) ;

int main(){

    //declytpe
    int a {9};
	double b{15.8};
	
/*

	fmt::println("size : {}" , sizeof(decltype((a > b)? a : b)) );//4

    decltype((a > b)? a : b) c {7}; // Declaring other variables through declytype
    fmt::println("c : {}" , c );
    fmt::println("sizeof(c) : {}" , sizeof(c) ); // 4
*/

   auto result = maximum(a,b);
   fmt::println( "result : {}" , result );
   fmt::println( "sizeof(result) :{}" , sizeof(result) );
    
    return 0;
}

//Definition
template <typename T, typename P>
auto maximum( T a, P b) -> decltype((a > b)? a : b) {
    return (a > b)? a : b;
}