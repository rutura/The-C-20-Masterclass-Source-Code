#include <iostream>
#include <concepts>

//Syntax1
/*
template <typename T>
requires std::integral<T>
T add( T a, T b){
    return a + b;
}
*/

//Syntax2
/*
template <std::integral T>
T add( T a, T b){
    return a + b;
}
*/

//Syntax3
/*
auto add(std::integral auto a , std::integral auto b){
    return a + b;
}
*/

//Syntax4
template <typename T>
T add( T a, T b) requires std::integral<T>{
    return a + b;
}

int main(){

   
	char a_0{10};
	char a_1{20};
	
	auto result_a = add(a_0,a_1);
	std::cout << "result_a : " << static_cast<int>(result_a) << std::endl;
	
	int b_0{11};
	int b_1{5};
	auto result_b = add(b_0,b_1);
	std::cout << "result_b : " << result_b << std::endl;


	double c_0 {11.1};
	double c_1 {1.9};
	auto result_c = add(c_0,c_1);
    std::cout << "result_c : " << result_c << std::endl;
 
  
    return 0;
}