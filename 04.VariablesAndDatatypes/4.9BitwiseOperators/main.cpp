/*
    . 
*/

#include <fmt/format.h>
#include <bitset>

int main() {
    //Printing integers in binary
    /*
    unsigned short int data {15};

    fmt::println("data (dec) : {0:d}", data);
    fmt::println("data (oct) : {0:o}", data);
    fmt::println("data (hex) : {0:x}", data);
    fmt::println("data (bin) : {:016b}", std::bitset<16>(data).to_ulong());
    */
 

    //Shift operators
    /*
    unsigned short int value {0xff0u};

    fmt::println("Size of short int {0}", sizeof(short int));//  16 bits

    fmt::println("(0)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("(1)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("(2)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("(3)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("(4)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("(5)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift right by one bit
    value = static_cast<unsigned short int>(value >> 1);
    fmt::println("(6)bin value : {:016b}, decimal value: {} ", value,value);

    //Shift by multiple bits in one go
    //Shift right by four bits 
    value = static_cast<unsigned short int>(value >> 4);
    fmt::println("(7)bin value : {:016b}, decimal value: {} ", value,value);
    */


   //--------------------------------------------------------------------------------------------------------------------

   //Logical bitwise operators
   /*
   int COLUMN_WIDTH {20};
    unsigned int value1 {0x3}; // 0000 0011
    unsigned int value2 {0x5}; // 0000 0101
	
    fmt::println("value1: {:032b}", value1);
    fmt::println("value2: {:032b}", value2);
    
	//AND
    fmt::println("Bitwise AND :");
    fmt::println("value1 & value2: {:032b}", value1 & value2);

	//OR
    fmt::println("Bitwise OR :");
    fmt::println("value1 | value2: {:032b}", value1 | value2);

    //NOT
    fmt::println("Bitwise NOT :");
    fmt::println("~value1: {:032b}", ~value1);
    fmt::println("~value2: {:032b}", ~value2);
	
	//XOR
    fmt::println("Bitwise XOR :");
    fmt::println("value1 ^ value2: {:032b}", value1 ^ value2);
    */
    
    return 0;
}