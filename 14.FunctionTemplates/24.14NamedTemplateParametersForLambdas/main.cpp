#include <iostream>


int main(){

    auto func =  [] <typename T, typename P>(T a, P b){
            return a + b;
    };

    char a {'c'};
    int b{63};

    auto result = func(a,b);
    std::cout << "result : " << result << std::endl;
    std::cout << "sizeof(result) : " << sizeof(result) << std::endl;
    
    
    return 0;
}