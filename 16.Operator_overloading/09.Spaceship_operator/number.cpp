#include "number.h"


/*
 //Implementations

Number::Number(int value) : m_wrapped_int(value) {}

std::ostream &operator<<(std::ostream &out, const Number &number)
{
  out << "Number : [" << number.m_wrapped_int << "]";
  return out;
}

// Comparison operators
// bool operator<(const Number& left_operand, const Number& right_operand){
//     return (left_operand.m_wrapped_int < right_operand.m_wrapped_int);
// }
// bool operator<(int left_operand, const Number& right_operand){
//     return (left_operand < right_operand.m_wrapped_int);
// }
// bool operator<(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int < right_operand);
// }


// bool operator==(const Number& left_operand, const Number& right_operand){
//     return (left_operand.m_wrapped_int == right_operand.m_wrapped_int);
// }
// bool operator==(int left_operand, const Number& right_operand){
//     return (left_operand == right_operand.m_wrapped_int);
// }
// bool operator==(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int == right_operand);
// }


// bool operator>(const Number& left_operand, const Number& right_operand){
//     return left_operand.m_wrapped_int > right_operand.m_wrapped_int;
// }
// bool operator>(int left_operand, const Number& right_operand){
//     return (left_operand > right_operand.m_wrapped_int);
// }
// bool operator>(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int > right_operand);
// }


// bool operator>=(const Number& left_operand, const Number& right_operand){
//    return !(left_operand.m_wrapped_int >= right_operand.m_wrapped_int);
// }
// bool operator>=(int left_operand, const Number& right_operand){
//     return (left_operand >= right_operand.m_wrapped_int);
// }
// bool operator>=(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int >= right_operand);
// }

// bool operator<=(const Number& left_operand, const Number& right_operand){
//     return !(left_operand.m_wrapped_int <= right_operand.m_wrapped_int);
// }
// bool operator<=(int left_operand, const Number& right_operand){
//     return (left_operand <= right_operand.m_wrapped_int);
// }
// bool operator<=(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int <= right_operand);
// }

// bool operator!=(const Number& left_operand, const Number& right_operand){
//     return !(left_operand.m_wrapped_int == right_operand.m_wrapped_int);
// }
// bool operator!=(int left_operand, const Number& right_operand){
//     return (left_operand != right_operand.m_wrapped_int);
// }
// bool operator!=(const Number& left_operand, int right_operand){
//     return (left_operand.m_wrapped_int != right_operand);
// }


Number::~Number() {}
 */

auto operator<=>(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() <=> right.get_wrapped_int());
}
auto operator<=>(int left, const Number &right) { return (left <=> right.get_wrapped_int()); }

bool operator==(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() == right.get_wrapped_int());
}

bool operator==(int left, const Number &right) { return (left == right.get_wrapped_int()); }

//Implementantions
Number::Number(int value) : m_wrapped_int(value) {}

std::ostream &operator<<(std::ostream &out, const Number &number)
{
  out << "Number : [" << number.m_wrapped_int << "]";
  return out;
}

Number::~Number() {}

