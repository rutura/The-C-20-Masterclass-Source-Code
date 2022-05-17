#include <iostream>
#include "compare.h" // Preprocessor
#include "operations.h"


int main(){

    int maximum = max(134,56);
    std::cout << "max : " << maximum << std::endl;

    int minimum = min(146,23);
    std::cout << "min : " << minimum << std::endl;

    int x{4}; // 5
    int y{5}; // 6

    int result = incr_mult(x,y);
    std::cout << "result : " << result << std::endl;
   
    return 0;
}

