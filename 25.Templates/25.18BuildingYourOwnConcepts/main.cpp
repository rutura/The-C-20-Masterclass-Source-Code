#include <iostream>
#include <type_traits>
#include <concepts>

//Syntax1
/*
template <typename T>
concept MyIntegral = std::is_integral_v<T>;

MyIntegral auto add( MyIntegral auto a, MyIntegral auto b) {
    return a + b;
}
*/


template <typename T>
concept Multipliable =  requires(T a, T b) {
	a * b; // Just makes sure the syntax is valid
};


template <typename T>
concept Incrementable = requires (T a) {
	a+=1;
	++a;
	a++;
};

template <typename T>
requires Incrementable<T>
T add (T a, T b){
    return a + b;
}


int main(){

    double x{6};
    double y{7};

    //std::string x{"Hello"};
    //std::string y{"World"};

    add(x,y);

    std::cout << "Done!" << std::endl;
    
    return 0;
}