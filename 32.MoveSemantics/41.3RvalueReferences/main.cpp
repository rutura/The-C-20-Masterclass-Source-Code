#include <iostream>

double add(double a , double b){
    return a + b;
}


int main(){
    
    int x{5};
    int y{10};

    int&& result = x + y;

    double&& outcome = add(10.1,20.2);


    //

    std::cout << "result : " << result << std::endl;
    std::cout << "outcome : " << outcome << std::endl;
   
    return 0;
}