#include <iostream>
#include <iomanip>
#include <bitset>


int main(){

	const int COLUMN_WIDTH {20};

	std::cout << std::endl;
	std::cout << "Compound bitwise assignment operators" << std::endl;
	
	unsigned char sandbox_var{0b00110100}; // 8 bits : positive numbers only
	
	//Print out initial value
	std::cout << std::endl;
	std::cout << "Initial value :  " << std::endl;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;
	
	//Compound left shift
	std::cout << std::endl;
	std::cout << "Shift left 2 bit positions in place :  " << std::endl;
	sandbox_var <<= 2;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;


    //Compound right shift
	std::cout << std::endl;
	std::cout << "Shift right 4 bit positions in place :  " << std::endl;
	sandbox_var >>= 4;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;

	//Compound OR with 0000 0010 to have all lower 4 bits turned on 
	std::cout << std::endl;
	std::cout << "Compound OR with 0000 0010 :  " << std::endl;
	sandbox_var |= 0b00001111;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;


	//Compound AND with 0000 1100 to turn off the 2 lowest bits
	std::cout << std::endl;
	std::cout << "Compound AND with 0000 1100 :  " << std::endl;
	sandbox_var &= 0b000000000;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;


	//XOR with 00000011 to turn on the 4 lowest bits again
	std::cout << std::endl;
	std::cout << "Compound XOR with 0000 0011 :  " << std::endl;
	sandbox_var ^= 0b00000011;
    std::cout << std::setw(COLUMN_WIDTH) << "sandbox_var : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(sandbox_var) << std::endl;
    std::cout << std::endl;


   


	
    
    return 0;
}