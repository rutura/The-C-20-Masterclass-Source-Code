#include <iostream>
#include <type_traits>


void func_floating_point  (double d) {
	std::cout << "func_floating_point called..." << std::endl;
} 
void func_integral(int i) { 
	std::cout << "func_integral called..." << std::endl;
} 

template <typename T>
void func(T t)
{
    if constexpr(std::is_integral_v<T>)
        func_integral(t);
    else if constexpr(std::is_floating_point_v<T>)
        func_floating_point(t);
    else
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
			"Argument must be integral or floating point");
}


int main(){

    func(12);

    return 0;
}