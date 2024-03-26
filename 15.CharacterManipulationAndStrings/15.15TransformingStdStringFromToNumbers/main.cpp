#include <fmt/format.h>
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
    
    fmt::println( "size of float_str : {}" , float_str.size());
    fmt::println( "float_var : {}" , float_var );
	fmt::println( "float_str : {}" , float_str);
	
    fmt::println( "double_var : {}" , double_var );
	fmt::println("double_str : {}" , double_str);
	
    fmt::println( "int_var : {}" , int_var );
	fmt::println( "int_str : {}" , int_str);
	*/


   //std::string to number (integral types)
	//int, long , long long
	//std::stoi, std::stol, std::stoll
	/*std::string number_str{"34.567"};//Could even be negative

	int int_var = std::stoi(number_str);
	fmt::println( "int_var : {}" , int_var );
	fmt::println( "sizeof(int_var) : {}" , sizeof(int_var) );
	
	long long_var = std::stol(number_str);
	fmt::println( "long_var : {}" , long_var );
	fmt::println( "sizeof(long_var) : {}" , sizeof(long_var) );
	
	long long long_long_var = std::stoll(number_str);
	fmt::println( "long_long_var : {}" , long_long_var );
	fmt::println( "sizeof(long_long_var) : {}" , sizeof(long_long_var) );
	*/

	//unsigned long , unsigned long long
	//std::stoul, std::stoull
	//Underflows when the std::string contains a negative number
	/*
	std::string number_str = "34.567";
	//std::string number_str = "-34.567"; // Resulting unsigned long and long long underflow
							// and become huge numbers of their type
	fmt::println( "unsigned long, unsigned long long : " );
	
	unsigned long u_l_var = std::stoul(number_str);
	fmt::println( "u_l_var : {}" , u_l_var );
	fmt::println( "sizeof(u_l_var) : {}" , sizeof(u_l_var) );
	
	unsigned long long u_ll_var = std::stoull(number_str);
	fmt::println( "u_ll_var : {}" , u_ll_var );
	fmt::println( "sizeof(u_ll_var) : {}" , sizeof(u_ll_var) );
	*/

	//float, double,long double : 
	//std::stof, std::stod, std::stold
    std::string number_str = "34.567";

	float float_var = std::stof(number_str);
	fmt::println( "float_var : {}" , float_var );
	fmt::println( "sizeof(float_var) : {}" , sizeof(float_var) );
	
	double double_var = std::stod(number_str);
	fmt::println( "double_var : {}" , double_var );
	fmt::println( "sizeof(double_var) : {}" , sizeof(double_var) );
	
	long double long_double_var = std::stold(number_str);
	fmt::println( "long_double_var : {}" , long_double_var );
	fmt::println( "sizeof(long_double_var) : {}" , sizeof(long_double_var) );







 



    return 0;
}