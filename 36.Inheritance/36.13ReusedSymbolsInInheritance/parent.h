#ifndef PARENT_H
#define PARENT_H

#include <fmt/format.h>

class Parent
{
public:
    Parent() = default;
    Parent(int member_var) : m_member_var(member_var){   
    }
    ~Parent() = default;
    
    void print_var()const{
        fmt::println( "The value in parent is : {}",  m_member_var);
    }
protected: 
    int m_member_var{100};
};


#endif // PARENT_H
