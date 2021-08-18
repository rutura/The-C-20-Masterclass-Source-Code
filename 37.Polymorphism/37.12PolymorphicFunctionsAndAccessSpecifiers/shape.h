#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <string>
class Shape
{
public:
    Shape();
    Shape(std::string_view description);
    ~Shape();
public:
    virtual void draw( )const{
        std::cout << "Shape::draw() called for : " << m_description << std::endl;
    }
private : 
	//Can be inherited even if it is private. Derived class will put 
	//this in public scope
    virtual void func() const {
        std::cout << "Shape::func() called for : " << m_description << std::endl;
    }
protected:
    std::string m_description;
};

#endif // SHAPE_H
