#include <iostream>

double sum ( double array[], size_t count){

	double sum{};
    for(size_t i{} ; i < count ; ++i){
        sum += array[i];
    }
    return sum;
	
}


int main(int argc, char **argv)
{
	double numbers[] {10.0,20.0,30.0,40.0,50.0}; // Sum should be 150.0
    
	double total = sum(numbers,std::size(numbers));
	
	std::cout << "sum : " << total << std::endl;
	
	return 0;
}