/*
    .
*/

#include <fmt/format.h>

const unsigned int mask_bit_0 {0b00000001} ;//Bit0
const unsigned int mask_bit_1 {0b00000010} ;//Bit1
const unsigned int mask_bit_2 {0b00000100} ;//Bit2
const unsigned int mask_bit_3 {0b00001000} ;//Bit3
const unsigned int mask_bit_4 {0b00010000} ;//Bit4
const unsigned int mask_bit_5 {0b00100000} ;//Bit5
const unsigned int mask_bit_6 {0b01000000} ;//Bit6
const unsigned int mask_bit_7 {0b10000000} ;//Bit7


void use_options_v0 (bool flag0, bool flag1, bool flag2, bool flag3,
            bool flag4, bool flag5, bool flag6, bool flag7){
                    
        fmt::println("Flag0 is: {}, do something with it.", flag0);
        fmt::println("Flag1 is: {}, do something with it.", flag1);
        fmt::println("Flag2 is: {}, do something with it.", flag2);
        fmt::println("Flag3 is: {}, do something with it.", flag3);
        fmt::println("Flag4 is: {}, do something with it.", flag4);
        fmt::println("Flag5 is: {}, do something with it.", flag5);
        fmt::println("Flag6 is: {}, do something with it.", flag6);
        fmt::println("Flag7 is: {}, do something with it.", flag7);
}


void use_options_v1(unsigned int flags){
   
        fmt::println("bit0 is {}, do something with it!", ((flags & mask_bit_0) >> 0));
        fmt::println("bit1 is {}, do something with it!", ((flags & mask_bit_1) >> 1));
        fmt::println("bit2 is {}, do something with it!", ((flags & mask_bit_2) >> 2));
        fmt::println("bit3 is {}, do something with it!", ((flags & mask_bit_3) >> 3));
        fmt::println("bit4 is {}, do something with it!", ((flags & mask_bit_4) >> 4));
        fmt::println("bit5 is {}, do something with it!", ((flags & mask_bit_5) >> 5));
        fmt::println("bit6 is {}, do something with it!", ((flags & mask_bit_6) >> 6));
        fmt::println("bit7 is {}, do something with it!", ((flags & mask_bit_7) >> 7));    
}

int main() {

  	use_options_v0(0,0,1,1,1,0,1,0);

    fmt::println("----------------------");
	use_options_v1(mask_bit_2 | mask_bit_3 | mask_bit_4 | mask_bit_6);

    //Packing color information
    fmt::println("----Packing color information.----");
    const unsigned int red_mask {0xFF000000};
    const unsigned int green_mask {0x00FF0000};
    const unsigned int blue_mask {0x0000FF00};
    const unsigned int alpha_mask {0x000000FF};// Transparency information
    
    
    unsigned int my_color {0xAABCDE00};
    
    //We shift to make sure the color byte of interest is in the 
    // lower index byte position so that we can interpret that as an integer,
    // which will be between 0 and 255. 
    
	//Set some format options
	
    fmt::println("Red is : {}", ((my_color & red_mask) >> 24));
    fmt::println("Green is : {}", ((my_color & green_mask) >> 16));
    fmt::println("Blue is : {}", ((my_color & blue_mask) >> 8));
    fmt::println("Alpha is : {}", ((my_color & alpha_mask) >> 0));
    return 0;
}