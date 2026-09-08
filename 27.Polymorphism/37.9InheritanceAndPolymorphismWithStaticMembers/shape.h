#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <string>
class Shape
{
public:
    Shape();
    Shape(std::string_view description);
    virtual ~Shape();
    void draw( )const{
        std::cout << "Shape::draw() called for : " << m_description << std::endl;
    }
    
    virtual int get_count() const{
        return m_count;
    }
    
    static int m_count;
protected:
    std::string m_description;

};

#endif // SHAPE_H
