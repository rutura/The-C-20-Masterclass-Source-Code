#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public : 
  //Constructors
  Point(double x, double y);
 
  Point(double xy_coord);       // Point Constructor
  Point();                  // Default constructor
  Point(const Point& point);    // Point Copy Constructor
  ~Point();                     // Point Destructor
 

  double length() const;   // Function to calculate distance from the point(0,0)
  
  static size_t get_point_count() {
      return m_point_count;
  }

  static void print_info(const Point& p){
		std::cout << "Point : [ m_x : " << p.m_x << ", m_y : " << p.m_y << "]" 
             << std::endl;
  }

private:
	double m_x;
	double m_y;
    inline static size_t m_point_count{};
 };



#endif // POINT_H
