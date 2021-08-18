#include <iostream>
#include <iomanip>
#include <bitset>

int main(){

    int COLUMN_WIDTH {20};
    unsigned char value1 {0x3}; // 0000 0011
    unsigned char value2 {0x5}; // 0000 0101
	

    std::cout << std::setw(COLUMN_WIDTH) << "value1 : " 
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(value1) << std::endl; 
		
	std::cout << std::setw(COLUMN_WIDTH) << "value2 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(value2) << std::endl;
    
	//AND
	std::cout << std::endl;
	std::cout << "Bitwise AND :  " << std::endl;
    std::cout << std::setw(COLUMN_WIDTH) << "value1 & value2 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(value1 & value2) << std::endl;
    std::cout << std::endl;

	//OR
	std::cout << std::endl;
	std::cout << "Bitwise OR :  " << std::endl;
    std::cout << std::setw(COLUMN_WIDTH) << "value1 | value2 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(value1 | value2) << std::endl;
    std::cout << std::endl;


    //NOT
	std::cout << std::endl;
    std::cout << "Bitwise NOT " << std::endl;
	
    std::cout << std::setw(COLUMN_WIDTH) << "~value1 : "
		<< std::setw(COLUMN_WIDTH) <<  std::bitset<8>(~value1) << std::endl;
		
    std::cout << std::setw(COLUMN_WIDTH) << "~value2 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(~value2) << std::endl;
		
    std::cout << std::setw(COLUMN_WIDTH) << "~01011001 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(~0b01011001) << std::endl;//Using bin literal
		
    std::cout << std::setw(COLUMN_WIDTH) << "~01011001 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(~0x59) << std::endl;//Using hex literal
    std::cout << std::endl; 


	//XOR
	std::cout << std::endl;
	std::cout << "Bitwise XOR :  " << std::endl;
    std::cout << std::setw(COLUMN_WIDTH) << "value1 ^ value2 : "
		<< std::setw(COLUMN_WIDTH) << std::bitset<8>(value1 ^ value2) << std::endl;
    std::cout << std::endl;



   
    return 0;
}