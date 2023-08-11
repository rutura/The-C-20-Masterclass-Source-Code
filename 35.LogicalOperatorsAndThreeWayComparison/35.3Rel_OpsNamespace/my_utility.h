#ifndef MY_UTILITY_H
#define MY_UTILITY_H

template< class T >
bool operator!=( const T& lhs, const T& rhs ) 
{
    return !(lhs == rhs);
}

template< class T >
bool operator>( const T& lhs, const T& rhs ) 
{
    return rhs < lhs;
}

template< class T >
bool operator<=( const T& lhs, const T& rhs ) 
{
    return !(rhs < lhs);
}

template< class T >
bool operator>=( const T& lhs, const T& rhs ) 
{
        return !(lhs < rhs);
}

#endif // MY_UTILITY_H