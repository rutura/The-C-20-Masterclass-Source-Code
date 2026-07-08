#ifndef POINT_H
#define POINT_H

#include <iostream> // Included just to get access to size_t

class Point
{
public:
  //Constructors
  Point(double x, double y);
  Point(double xy_coord);       // Point Constructor
  Point();                  // Default constructor
  Point(const Point& point);    // Point Copy Constructor
  ~Point();                     // Point Destructor
  double length() const;   // Function to calculate distance from the point(0,0)
  
  size_t get_point_count() const{
	 return m_point_count;
  }

  void print_info()const{
    std::cout << "Point  [ &m_x : " << &m_x << ", &m_y : " << &m_y << "]" << std::endl;
  }
  
private:
  double m_x;
  double m_y;
  inline static size_t m_point_count {}; // C++17
};
#endif // POINT_H
