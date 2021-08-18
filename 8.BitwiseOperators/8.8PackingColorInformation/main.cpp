#include <iostream>


int main(){

    const unsigned int red_mask {0xFF000000};
    const unsigned int green_mask {0x00FF0000};
    const unsigned int blue_mask {0x0000FF00};
    const unsigned int alpha_mask {0x000000FF};// Transparency information
    
    
    unsigned int my_color {0xAABCDE00};
    
    //We shift to make sure the color byte of interest is in the 
    // lower index byte position so that we can interpret that as an integer,
    // which will be between 0 and 255. 
    
	//Set some format options
	std::cout << std::dec << std::showbase << std::endl;
	
    std::cout << "Red is : " <<  ((my_color & red_mask) >> 24) << std::endl;
    std::cout << "Green is : " <<  ((my_color & green_mask) >> 16) << std::endl;
    std::cout << "Blue is : " <<  ((my_color & blue_mask) >> 8) << std::endl;
    std::cout << "Alpha is : " <<  ((my_color & alpha_mask) >> 0) << std::endl;
    
    return 0;
}