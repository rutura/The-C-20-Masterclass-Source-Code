#include <iostream>

int main(){

    //The comma operator combines
    //two or more  expressions into a single expression,
    // where the value of the operation is the value of its right operand
    
    int increment {5};
    int number1 {10};
    int number2 {20};
    int number3 {25};
    int result = (number1 *= ++increment, number2 - (++increment), number3 += ++increment);
    std::cout << "number1 : " << number1 << std::endl; // 60
    std::cout << "number2 : " << number2 << std::endl; // 20
    std::cout << "number3 : " << number3 << std::endl; // 33
    std::cout << "result : " <<  result << std::endl; // 33
   
    return 0;
}