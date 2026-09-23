#include <iostream>
#include <print>

const int leg_count{ 2 };


void call_count() {
	static int count{ 0 };
	++count;
	std::println("Count: {}", count);
}


double multiply_by_2(double a) {
	double result = a * 2;
	return result;
}


int main(){

	call_count();
	call_count();

}