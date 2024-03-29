#ifndef SHAPE_H
#define SHAPE_H
#include <fmt/format.h>
#include <string>
class Shape
{
public:
    Shape();
    Shape(std::string_view description);
    ~Shape();
public:
     void draw( )const{
        fmt::println( "Shape::draw() called for : {}", m_description );
    }
private : 
     void func() const {
        fmt::println( "Shape::func() called for : {}" , m_description );
    }
protected:
    std::string m_description;
};

#endif // SHAPE_H
