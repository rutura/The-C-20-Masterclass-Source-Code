#include <iostream>

//Declaration
template <typename T, typename P>
auto maximum( T a, P b) -> decltype((a > b)? a : b) ;

int main(){

    //declytpe
    int a {9};
	double b{15.8};
	

    /*
	std::cout << "size : " << sizeof(decltype((a > b)? a : b)) << std::endl;//4

    decltype((a > b)? a : b) c {7}; // Declaring other variables through declytype
    std::cout << "c : " << c << std::endl;
    std::cout << "sizeof(c) : " << sizeof(c) << std::endl; // 4
    */

   auto result = maximum(a,b);
   std::cout << "result : " << result << std::endl;
   std::cout << "sizeof(result) :" << sizeof(result) << std::endl;
    
    return 0;
}

//Definition
template <typename T, typename P>
auto maximum( T a, P b) -> decltype((a > b)? a : b) {
    return (a > b)? a : b;
}