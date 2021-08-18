#include <iostream>
#include <string>


int main(){

	//Number to String : the std::to_string function.
    /*
    float float_var {22.3f};
    double double_var {1.34847e5};
    int int_var {223};
    
    std::string float_str {std::to_string(float_var)};;
    std::string double_str{std::to_string(double_var)};;
    std::string int_str{std::to_string(int_var)};
    
    std::cout << "size of float_str : " << float_str.size()<< std::endl;
    std::cout << "float_var : " << float_var << std::endl;
	std::cout << "float_str : " << float_str<< std::endl;
	
    std::cout << "double_var : " << double_var << std::endl;
	std::cout <<"double_str : " << double_str<< std::endl;
	
    std::cout << "int_var : " << int_var << std::endl;
	std::cout << "int_str : " << int_str<< std::endl;

    */

   //std::string to number (integral types)
	//int, long , long long
	//std::stoi, std::stol, std::stoll
    /*
	std::string number_str{"34.567"};//Could even be negative

	int int_var = std::stoi(number_str);
	std::cout << "int_var : " << int_var << std::endl;
	std::cout << "sizeof(int_var) : " << sizeof(int_var) << std::endl;
	
	long long_var = std::stol(number_str);
	std::cout << "long_var : " << long_var << std::endl;
	std::cout << "sizeof(long_var) : " << sizeof(long_var) << std::endl;
	
	long long long_long_var = std::stoll(number_str);
	std::cout << "long_long_var : " << long_long_var << std::endl;
	std::cout << "sizeof(long_long_var) : " << sizeof(long_long_var) << std::endl;
    */

	//unsigned long , unsigned long long
	//std::stoul, std::stoull
	//Underflows when the std::string contains a negative number
	/*
	std::string number_str = "34.567";
	//std::string number_str = "-34.567"; // Resulting unsigned long and long long underflow
							// and become huge numbers of their type
	std::cout << std::endl;
	std::cout << "unsigned long, unsigned long long : " << std::endl;
	
	unsigned long u_l_var = std::stoul(number_str);
	std::cout << "u_l_var : " << u_l_var << std::endl;
	std::cout << "sizeof(u_l_var) : " << sizeof(u_l_var) << std::endl;
	
	unsigned long long u_ll_var = std::stoull(number_str);
	std::cout << "u_ll_var : " << u_ll_var << std::endl;
	std::cout << "sizeof(u_ll_var) : " << sizeof(u_ll_var) << std::endl;
    */

	//float, double,long double : 
	//std::stof, std::stod, std::stold
    std::string number_str = "34.567";

	float float_var = std::stof(number_str);
	std::cout << "float_var : " << float_var << std::endl;
	std::cout << "sizeof(float_var) : " << sizeof(float_var) << std::endl;
	
	double double_var = std::stod(number_str);
	std::cout << "double_var : " << double_var << std::endl;
	std::cout << "sizeof(double_var) : " << sizeof(double_var) << std::endl;
	
	long double long_double_var = std::stold(number_str);
	std::cout << "long_double_var : " << long_double_var << std::endl;
	std::cout << "sizeof(long_double_var) : " << sizeof(long_double_var) << std::endl;







 



    return 0;
}