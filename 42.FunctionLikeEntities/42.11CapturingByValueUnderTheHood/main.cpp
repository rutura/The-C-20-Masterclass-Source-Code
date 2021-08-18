#include <iostream>


int main(){

    int a{7};
    int b {3};
    int some_var{28};// Not captured by the [=] lambda, so it won't set up a member var 
                    // for this
    double some_other_var{55.5}; // Not captured by the [=] lambda, so it won't set up 
                                // a member var for this.

    //Capturing  everything by value 
    auto func = [=] (int c, int d)  {
        std::cout << "Captured values : " << std::endl;
        std::cout << "a : " << a << std::endl;
        std::cout << "b : " << b  << std::endl;
        
        std::cout << std::endl;
        
        std::cout << "Parameters : " << std::endl;
        std::cout << "c : " << c << std::endl;
        std::cout << "d : " << d << std::endl;
    };
    func(10,20);

    std::cout << "----" << std::endl;
    func(20,30);
   
    return 0;
}