#include <iostream>

int max(int& a, int&b){
    std::cout << "max with int& called" << std::endl;

    //Can change a and b through the reference 
    //a = 200;// This change will be visible outside the function
    
    return (a > b)? a : b;
}

int max(const int& a, const int& b){
    std::cout << "max with const int& called" << std::endl;
    
    //Can NOT change a and b through the reference 
    //a = 200; // Will give a compiler error.
    return (a > b)? a : b;
}


int main(){

	int a{45};
    int b{85};
    
    int max1 = max(a,b);
    std::cout << "max1 : " << max1 << std::endl;

    const int& ref_a = a;
    const int& ref_b = b;

    int max2 = max(ref_a,ref_b);
    std::cout << "max2 : " << max2 << std::endl;  

   
    return 0;
}