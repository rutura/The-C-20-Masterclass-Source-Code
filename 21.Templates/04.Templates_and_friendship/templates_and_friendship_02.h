/*
    Any template instantiations of print_point, regardless of the template argument,
    can access the private members of the Point class.
    Notice the syntax used to declare it as a friend of the Point class:
    it uses the template syntax. The same applies to the class template Canvas. It's declared as a friend of the Point class and any template instantiation, regardless of the template argument, can access its private parts.
*/
#pragma once

#include <fmt/format.h>


namespace templates_and_friendship_02 {

//The class is not a template, but the friend function and class are templates.
class Point
{

  template<typename T> friend class Canvas;

  template<typename T> friend void print_point(const Point &p);

  int x;
  int y;

public:
  Point(int x, int y)
    : x(x), y(y) {}

};

template<typename T> class Canvas
{
public:
  void draw(const Point &p) { fmt::print("Drawing point: ({}, {})\n", p.x, p.y); }
};

template<typename T> void print_point(const Point &p) { fmt::print("Point: ({}, {})\n", p.x, p.y); }

}// namespace templates_and_friendship_02