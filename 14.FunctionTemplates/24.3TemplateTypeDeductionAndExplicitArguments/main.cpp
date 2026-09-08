#include <iostream>
#include <string>

template <typename T> T maximum( T a, T b){
    return (a > b) ? a : b;
}

int main(){

	int a{10};
	int b{23};
	double c{34.7};
	double d{23.4};
	std::string e{"hello"};
	std::string f{"world"};

    //Explicit template arguments

    auto max = maximum<double>(a,f);
    std::cout << "max : " << max << std::endl;
   
    return 0;
}