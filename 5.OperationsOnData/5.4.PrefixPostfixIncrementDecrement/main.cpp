#include <iostream>

int main(){

	int value { 5 };
    
    //Increment by one
    value = value + 1; //6
    std::cout << "The value is : " << value << std::endl; // 6
    
    value = 5; // Reset value to 5
    
    //Decrement by one
    value = value - 1; // 4
    std::cout << "The value is : " << value << std::endl; //4
    
    //===================================================================

    
    std::cout << "======Postfix increment and decrement======"<< std::endl;
    //Reset value to 5
    value = 5;
    
    std::cout << "The value is (incrementing) : " << value++ << std::endl; // 5
    std::cout << "The value is : " << value << std::endl; // 6
    
    std::cout << std::endl;
    
    //Decrement with postfix
    
    //Reset value to 5
    value = 5;
    
    std::cout << "The value is (decrementing) : " << value-- << std::endl; //5
    std::cout << "The value is : " << value << std::endl; // 4


    //===================================================================

    
    std::cout << "======Prefix increment and decrement======"<< std::endl;

    //Reset value to 5
    value = 5;
    
    ++value;
    std::cout << "The value is (prefix++) : " << value << std::endl; // 6
    
    //Reset value to 5
    value = 5;
    std::cout << "The value is (prefix++ in place) : " << ++value << std::endl; // 6
    
    std::cout << std::endl;
    
    //Prefix : Decrementing
    
    //Reset value to 5;
    value = 5;
    --value;
    std::cout << "The value is (prefix--) : " << value << std::endl; // 4
    
    //Reset value to 5;
    value = 5;
    std::cout << "The value is (prefix-- in place) : " << --value << std::endl;//4

   
    return 0;
}