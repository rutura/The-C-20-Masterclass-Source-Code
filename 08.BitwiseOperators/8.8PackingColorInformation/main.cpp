#include <fmt/format.h>


int main(){

    const unsigned int red_mask {0xFF000000};
    const unsigned int green_mask {0x00FF0000};
    const unsigned int blue_mask {0x0000FF00};
    const unsigned int alpha_mask {0x000000FF};// Transparency information
    
    
    unsigned int my_color {0xAABCDE00};
    
    //We shift to make sure the color byte of interest is in the 
    // lower index byte position so that we can interpret that as an integer,
    // which will be between 0 and 255. 

	
    fmt::println( "Red is : {0:d}" ,  ((my_color & red_mask) >> 24) );
    fmt::println( "Green is : {0:d}" ,  ((my_color & green_mask) >> 16) );
    fmt::println( "Blue is : {0:d}" ,  ((my_color & blue_mask) >> 8) );
    fmt::println( "Alpha is : {0:d}" ,  ((my_color & alpha_mask) >> 0) );
    
    return 0;
}