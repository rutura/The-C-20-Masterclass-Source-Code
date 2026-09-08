#include "outer.h"
Outer::Outer(int int_param, double double_param)
    : m_var1(int_param) , m_var2(double_param)
{
}

//default constructor . Delegates to two param constructor
Outer::Outer() : Outer(0,0.0){
    
}

Outer::~Outer()
{
}

Outer::Inner::Inner(double double_param) : inner_var(double_param){
    
}

