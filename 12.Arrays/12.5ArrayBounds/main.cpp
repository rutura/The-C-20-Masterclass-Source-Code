#include <fmt/format.h>


int main(){

	int numbers[] {1,2,3,4,5,6,7,8,9,0};
	
	//Read beyond bounds : Will read garbage or crash your program
	//fmt::println("numbers[12] : {}",  numbers[12]);

	//Write beyond bounds. The compiler allows it. But you don't own 
	//the memory at index 12, so other programs may modify it and your
	//program may read bogus data at a later time. Or you can even
	//corrupt data used by other parts of your ptogram

	numbers[129] = 1000;
	fmt::println( "numbers[129] : {}" ,numbers[129] );

    fmt::println( "Program ending...." );

    
    return 0;
}