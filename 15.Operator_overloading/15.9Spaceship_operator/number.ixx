module;

#include <iostream>
#include <fmt/format.h>

export module number;

//#7: Logical operators simplified.
/*
export class Number
{

  friend std::ostream &operator<<(std::ostream &out, const Number &number);

  // Comparison operators
//   friend bool operator<(const Number& left_operand, const Number& right_operand);
//   friend bool operator<(int left_operand, const Number& right_operand);
//   friend bool operator<(const Number& left_operand, int right_operand);

//   friend bool operator==(const Number& left_operand, const Number& right_operand);
//   friend bool operator==(int left_operand, const Number& right_operand);
//   friend bool operator==(const Number& left_operand, int right_operand);

//   friend bool operator>(const Number& left_operand, const Number& right_operand);
//   friend bool operator>(int left_operand, const Number& right_operand);
//   friend bool operator>(const Number& left_operand, int right_operand);

//   friend bool operator>=(const Number& left_operand, const Number& right_operand);
//   friend bool operator>=(int left_operand, const Number& right_operand);
//   friend bool operator>=(const Number& left_operand, int right_operand);

//   friend bool operator<=(const Number& left_operand, const Number& right_operand);
//   friend bool operator<=(int left_operand, const Number& right_operand);
//   friend bool operator<=(const Number& left_operand, int right_operand);

//   friend bool operator!=(const Number& left_operand, const Number& right_operand);
//   friend bool operator!=(int left_operand, const Number& right_operand);
//   friend bool operator!=(const Number& left_operand, int right_operand);


public:
  Number() = delete;
  explicit Number(int value);

  // getter
  int get_wrapped_int() const { return m_wrapped_int; }

  auto operator<=>(const Number &right) const = default;
  auto operator<=>(int n) const { return m_wrapped_int <=> n; }
  bool operator==(const Number &right) const { return m_wrapped_int == right.m_wrapped_int; }
  bool operator==(int n) { return m_wrapped_int == n; }

  ~Number();

private:
  int m_wrapped_int{ 0 };
};

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


//#8: spaceship operator as a non member
class Number
{
  friend std::ostream &operator<<(std::ostream &out, const Number &number);
  friend struct fmt::formatter<Number>;

public:
  Number() = delete;
  explicit Number(int value);

  // getter
  int get_wrapped_int() const { return m_wrapped_int; }

  // auto operator<=>(const Number& right) const = default;
  // auto operator<=> (int n) const{
  //     return m_wrapped_int <=> n;
  // }
  // bool operator==(const Number& right) const{
  //     return m_wrapped_int == right.m_wrapped_int;
  // }
  // bool operator==(int n){
  //     return m_wrapped_int == n;
  // }

  ~Number();

private:
  int m_wrapped_int{ 0 };
};

inline auto operator<=>(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() <=> right.get_wrapped_int());
}
inline auto operator<=>(int left, const Number &right) { return (left <=> right.get_wrapped_int()); }

inline bool operator==(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() == right.get_wrapped_int());
}

inline bool operator==(int left, const Number &right) { return (left == right.get_wrapped_int()); }

//Implementantions
Number::Number(int value) : m_wrapped_int(value) {}

std::ostream &operator<<(std::ostream &out, const Number &number)
{
  out << "Number : [" << number.m_wrapped_int << "]";
  return out;
}

Number::~Number() {}

