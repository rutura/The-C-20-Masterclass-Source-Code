
#include <fmt/format.h>

class Number
{
  friend std::ostream &operator<<(std::ostream &out, const Number &number);
  friend struct fmt::formatter<Number>;
  // Arithmetic operators
  friend Number operator+(const Number &left_operand, const Number &right_operand);
  friend Number operator-(const Number &left_operand, const Number &right_operand);
  friend Number operator*(const Number &left_operand, const Number &right_operand);
  friend Number operator/(const Number &left_operand, const Number &right_operand);
  friend Number operator%(const Number &left_operand, const Number &right_operand);

public:
  Number() = default;
  Number(int value);


  explicit operator double() const { return (static_cast<double>(m_wrapped_int)); }

  /*
  //Implicit conversions won't work for the first operand
  Number operator+(const Number& right) const{
      return Number(m_wrapped_int + right.m_wrapped_int);
  }
  */

  // getter
  int get_wrapped_int() const { return m_wrapped_int; }

  ~Number();

private:
  int m_wrapped_int{ 0 };
};

template<> struct fmt::formatter<Number>
{
  constexpr parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Number &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Number : [{}]", obj.m_wrapped_int);
  }
};