#include "my_utility.h"
#include "point.h"

bool operator!=( const Point& lhs, const Point& rhs )
{
    return !(lhs == rhs);
}

bool operator>( const Point& lhs, const Point& rhs )
{
    return rhs < lhs;
}

bool operator<=( const Point& lhs, const Point& rhs )
{
    return !(rhs < lhs);
}

bool operator>=( const Point& lhs, const Point& rhs )
{
    return !(lhs < rhs);
}
