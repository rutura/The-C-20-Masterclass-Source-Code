/*
    . Exploring some math functions.
*/
#include <fmt/format.h>

int main(){

	double weight { 7.7 };
    
    //floor
    fmt::println("Weight rounded to floor is : {}", std::floor(weight));

    //ceil 
    fmt::println("Weight rounded to ceil is : {}", std::ceil(weight));

    //abs
    double savings {-5000 };

    fmt::println("Abs of weight is : {}", std::abs(weight));
    fmt::println("Abs of savings is : {}", std::abs(savings));
    
    //exp : f(x) = e ^ x , where e = 2.71828 . Test the result here against a calculator
    double exponential = std::exp(10);
    fmt::println("The exponential of 10 is : {}", exponential);  
    //pow
    fmt::println("3^4 is : {}", std::pow(3,4));
    fmt::println("9^3 is : {}", std::pow(9,3));

    //log : reverse function of pow. if 2^3 = 8 , log 8 in base 2 = 3.  Log is like asking
    // to which exponent should we elevate 2 to get eight ? Log, by default computes the log
    // in base e. There also is another function which uses base 10 called log10
    
    // Try the reverse operation of  e^4 = 54.59 , it will be log 54.59 in base e = ? 
    fmt::println("Log ; to get 54.59, you would elevate e to the power of : {}", std::log(54.59)); 
    //log10 , 10 ^ 4 = 10000  , to get 10k , you'd need to elevate 10 to the power of ? , this is log in base 10
    fmt::println("To get 10000, you'd need to elevate 10 to the power of : {}",
                 std::log10(10000)); // 4
    //sqrt
    fmt::println("The square root of 81 is : {}", std::sqrt(81));

    //round. Halfway points are rounded away from 0. 2,5 is rounded to 5 for example
    fmt::println("3.654 rounded to : {}", std::round(3.654));
    fmt::println("2.5 is rounded to : {}", std::round(2.5));
    fmt::println("2.4 is rounded to : {}", std::round(2.4));
    return 0;
}