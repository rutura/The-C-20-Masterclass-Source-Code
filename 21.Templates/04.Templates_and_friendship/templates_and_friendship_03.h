/*
   Friendship is only granted to a select group of specializations of the friend function or friend class.
   Int instances specifically
   print_point<double> and Canvas<double> cannot access the private members of Point for example. 
*/
#pragma once

#include <fmt/format.h>


namespace templates_and_friendship_03 {

class Point;//Forward declaration

template<typename T> void print_point(const Point &p);//Forward declaration

template<typename T> class Canvas;//Forward declaration

class Point
{
  //Only int instances of the friends have access to the private members of any instance Point class.
  friend void print_point<int>(const Point &p);
  friend class Canvas<int>;

  int x;
  int y;

public:
  Point(int x, int y)
    : x(x), y(y) {}
};

//Definition if print_point
template<typename T> void print_point(const Point &p) { fmt::print("Point: ({}, {})\n", p.x, p.y); }

//Definition of Canvas
template<typename T> class Canvas
{
public:
  void draw(const Point &p) { fmt::print("Drawing point: ({}, {})\n", p.x, p.y); }
};

//Specializations
/*
template <>
void print_point<int>(const Point& p) {
    fmt::println("Point - function specialization : ({}, {})\n", p.x, p.y);
}


template <>
class Canvas<int> {
public:
    void draw(const Point& p) {
        fmt::println("Drawing point - specialization: ({}, {})\n", p.x, p.y);
    }
};
*/


}// namespace templates_and_friendship_03