#include "point.h"

Point::Point(double x_param, double y_param) : x(new double(x_param)), y(new double(y_param))
{
  fmt::println("Point constructed  : {}", fmt::ptr(this));
}
/*
//Copy constructor
Point::Point(const Point& source_point)
        : x(new double(*(source_point.get_x()))),
                y(new double(*(source_point.get_y())))
{
        fmt::println( "Body of copy constructor" );
}

//Move constructor
Point::Point( Point&& source_point)
        : x(source_point.steal_x()),
                y(source_point.steal_y())
{
    //source_point.invalidate();
        fmt::println( "Body of move constructor" );
}
*/


Point::~Point()
{
  delete x;
  delete y;
}
