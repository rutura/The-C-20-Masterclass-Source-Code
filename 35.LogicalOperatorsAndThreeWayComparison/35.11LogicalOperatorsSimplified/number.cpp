#include "number.h"

Number::Number(int value) : m_wrapped_int(value) {}

std::ostream &operator<<(std::ostream &out, const Number &number)
{
  out << "Number : [" << number.m_wrapped_int << "]";
  return out;
}

template<> struct fmt::formatter<Number> : nested_formatter<int>
{
  auto format(Number n, format_context &ctx) const
  {
    return write_padded(ctx, [=](auto out) { return format_to(out, "Number: [{}]", nested(n.get_wrapped_int())); });
  }
};

// Comparison operators
/*
bool operator<(const Number& left_operand, const Number& right_operand){
    return (left_operand.m_wrapped_int < right_operand.m_wrapped_int);
}
bool operator<(int left_operand, const Number& right_operand){
    return (left_operand < right_operand.m_wrapped_int);
}
bool operator<(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int < right_operand);
}


bool operator==(const Number& left_operand, const Number& right_operand){
    return (left_operand.m_wrapped_int == right_operand.m_wrapped_int);
}
bool operator==(int left_operand, const Number& right_operand){
    return (left_operand == right_operand.m_wrapped_int);
}
bool operator==(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int == right_operand);
}


bool operator>(const Number& left_operand, const Number& right_operand){
    return left_operand.m_wrapped_int > right_operand.m_wrapped_int;
}
bool operator>(int left_operand, const Number& right_operand){
    return (left_operand > right_operand.m_wrapped_int);
}
bool operator>(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int > right_operand);
}


bool operator>=(const Number& left_operand, const Number& right_operand){
   return !(left_operand.m_wrapped_int >= right_operand.m_wrapped_int);
}
bool operator>=(int left_operand, const Number& right_operand){
    return (left_operand >= right_operand.m_wrapped_int);
}
bool operator>=(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int >= right_operand);
}

bool operator<=(const Number& left_operand, const Number& right_operand){
    return !(left_operand.m_wrapped_int <= right_operand.m_wrapped_int);
}
bool operator<=(int left_operand, const Number& right_operand){
    return (left_operand <= right_operand.m_wrapped_int);
}
bool operator<=(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int <= right_operand);
}

bool operator!=(const Number& left_operand, const Number& right_operand){
    return !(left_operand.m_wrapped_int == right_operand.m_wrapped_int);
}
bool operator!=(int left_operand, const Number& right_operand){
    return (left_operand != right_operand.m_wrapped_int);
}
bool operator!=(const Number& left_operand, int right_operand){
    return (left_operand.m_wrapped_int != right_operand);
}
*/


Number::~Number() {}
