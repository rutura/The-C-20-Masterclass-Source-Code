#ifndef POINT_H
#define POINT_H

#include <iostream>

#include "integer.h"

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
  
  size_t get_point_count() const{
      return m_point_count;
  }

	// Members of other objects
	Integer i1{1};
	const Integer i2{2}; 
	static inline Integer i3{3};
	static inline const Integer i4{4};
	
	Integer* p_i5{nullptr};
	static Integer i6;
	static const Integer i7;
private:
	double m_x;
	double m_y;
    static size_t m_point_count;
 };



#endif // POINT_H
