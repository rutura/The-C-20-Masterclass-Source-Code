#include <fmt/format.h>
#include <bitset>

/**
* Printing binary representation of decimals (base 2)
*/
int main(){

	unsigned short int value {0xff0u};

	fmt::println("Size of short int : {}" ,  sizeof(short int));//  16 bits
	
    fmt::println("value: {:016b}, dec : {}",  std::bitset<16>(value).to_ulong(), value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("value: {:016b}, , dec : {}" ,  std::bitset<16>(value).to_ulong() , value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("value: {:016b}, dec : {}", std::bitset<16>(value).to_ulong() , value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("value :{:016b}, dec : {} ",  std::bitset<16>(value).to_ulong() , value);


    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("value: {:016b}, , dec : {}", std::bitset<16>(value).to_ulong(),value);

    //Shift left by one bit
    value = static_cast<unsigned short int>(value << 1);
    fmt::println("value: {:016b}, dec : {}", std::bitset<16>(value).to_ulong(), value);

    //Shift right by one bit
    value = static_cast<unsigned short int>(value >> 1);
    fmt::println("value: {:016b}, dec : {}", std::bitset<16>(value).to_ulong(), value);


    //Shift by multiple bits in one go
    //Shift right by four bits 
    value = static_cast<unsigned short int>(value >> 4);
    fmt::println("value: {:016b}, dec : {}", std::bitset<16>(value).to_ulong() , value);



    //
    fmt::println("value: {:016b}",  (value >> 1));








   
    return 0;
}