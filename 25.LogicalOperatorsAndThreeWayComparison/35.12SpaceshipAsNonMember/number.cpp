#include "number.h"

Number::Number(int value) : m_wrapped_int(value)
{
}

std::ostream& operator<<(std::ostream& out , const Number& number){
    out << "Number : [" << number.m_wrapped_int << "]";
    return out;
}

Number::~Number()
{
}


