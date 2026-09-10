#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square
{
public:
	 explicit Square(double side_param);
     Square( double side_param, const std::string& color_param, int shading_param);
	 ~Square();
    double surface() const;
    
private :
    double m_side;
    std::string m_color;
    int m_shading;
    double m_position;
};

#endif // SQUARE_H
