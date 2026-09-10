#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square
{
public:
	 explicit Square(double side_param , const std::string& color_param = "black");
	 ~Square();
    double surface() const;
    
private :
    double m_side;
    std::string m_color;
};

#endif // SQUARE_H
