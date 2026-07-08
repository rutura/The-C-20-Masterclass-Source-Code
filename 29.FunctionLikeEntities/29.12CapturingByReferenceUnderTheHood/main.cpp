#include <iostream>


int main(){

    int a{7};
    int b {3};
    int some_var{28};// Not captured by the [=] lambda, so it won't set up a member var  for this
    double some_other_var{55.5}; // Not captured by the [=] lambda, so it won't set up   a member var for this.
      

    //Capturing a few variables by reference
    auto func = [&a,&b] (int c, int d){
        ++a; // Modifying member vars allowed by default.
        std::cout << "Captured values : ";
        std::cout << " a : " << a ;
        std::cout << " b : " << b ;
        
        std::cout << std::endl;
        std::cout << "Parameters : ";
        std::cout << " c : " << c;
        std::cout << " d : " << d;
        std::cout << std::endl;
    };

    func(10,20);
    std::cout << "a : " << a << std::endl;
    
    return 0;
}