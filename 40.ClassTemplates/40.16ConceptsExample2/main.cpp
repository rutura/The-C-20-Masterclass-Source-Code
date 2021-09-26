#include <iostream>
#include <concepts>

template <typename T>
concept Number = (std::integral<T> || std::floating_point<T>) 
                 && !std::same_as<T, bool>
                 && !std::same_as<T, char>;


template <Number T, Number  U>
auto add ( T a, U b){
    return a + b;
}


int main(){

    static_assert(Number<int>);
    //auto result = add(20.1, 20);
    //std::cout << "result :  " << result << std::endl;
   
    return 0;
}