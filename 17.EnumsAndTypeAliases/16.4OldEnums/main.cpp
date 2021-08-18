#include <iostream>

enum   Direction : unsigned char  {
    TopLeft = 64, TopRight,Center,BottomLeft,BottomRight
};
    
enum   Tool {
    Pen,Marker, Eraser,Rectangle,Circle,PaintBucket
};


int main(){

	Direction direction{Direction::TopLeft};
	Tool tool {Tool::Pen};

    std::cout << "direction : " << static_cast<unsigned int>(direction) << std::endl;
    std::cout << "tool : " << tool << std::endl;
    //std::cout << "(tool > direction) : " << (tool > direction) << std::endl;
   
    return 0;
}