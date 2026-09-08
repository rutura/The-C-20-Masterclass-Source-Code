
#include <iostream>

int& adjust( int& input);
int sum(int x , int y);


int main(int argc, char **argv){

	int a{10};
	int b{12};

	int summation  =  sum( a , b);
	std::cout << "sum : " 
		<< summation << std::endl;

	return 0;
}

int& adjust( int& input){
	int adjustment{2};
	input += adjustment;
	return input;
}

int sum(int x , int y){

	int result = x + y;
	adjust(result);
	return result;
}

