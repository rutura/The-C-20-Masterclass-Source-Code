#include <iostream>


void print_sum(int a, int b){
	
	int sum = a + b;
	std::cout << "sizeof(a) : " << sizeof(a) << std::endl;
	std::cout << "sizeof(b) : " << sizeof(b) << std::endl;
    std::cout << "sizeof(int) : " << sizeof(int) << std::endl;
    std::cout << "sizeof(double) : " << sizeof(double) << std::endl;
	std::cout << "sum : " << sum << std::endl;
	std::cout << std::endl;
}


int main(){

    double a{4.5};
    double b{7.8};

    print_sum(a,b);
   
    return 0;
}