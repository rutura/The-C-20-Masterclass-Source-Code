#ifndef MY_UTILITY_H
#define MY_UTILITY_H

class Point;

bool operator!=( const Point& lhs, const Point& rhs );
bool operator>( const Point& lhs, const Point& rhs );
bool operator<=( const Point& lhs, const Point& rhs );
bool operator>=( const Point& lhs, const Point& rhs );

#endif // MY_UTILITY_H