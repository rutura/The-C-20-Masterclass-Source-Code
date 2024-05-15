#ifndef NUMBER_H
#define NUMBER_H
#include <fmt/format.h>

class Number
{
  friend std::ostream &operator<<(std::ostream &out, const Number &number);
  friend struct fmt::formatter<Number>;
  // Comparison operators
  friend bool operator<(const Number &left_operand, const Number &right_operand);
  friend bool operator<(int left_operand, const Number &right_operand);
  friend bool operator<(const Number &left_operand, int right_operand);

  friend bool operator==(const Number &left_operand, const Number &right_operand);
  friend bool operator==(int left_operand, const Number &right_operand);
  friend bool operator==(const Number &left_operand, int right_operand);

  friend bool operator>(const Number &left_operand, const Number &right_operand);
  friend bool operator>(int left_operand, const Number &right_operand);
  friend bool operator>(const Number &left_operand, int right_operand);

  friend bool operator>=(const Number &left_operand, const Number &right_operand);
  friend bool operator>=(int left_operand, const Number &right_operand);
  friend bool operator>=(const Number &left_operand, int right_operand);

  friend bool operator<=(const Number &left_operand, const Number &right_operand);
  friend bool operator<=(int left_operand, const Number &right_operand);
  friend bool operator<=(const Number &left_operand, int right_operand);

  friend bool operator!=(const Number &left_operand, const Number &right_operand);
  friend bool operator!=(int left_operand, const Number &right_operand);
  friend bool operator!=(const Number &left_operand, int right_operand);

public:
  Number() = default;
  explicit Number(int value);

  // getter
  int get_wrapped_int() const { return m_wrapped_int; }

  ~Number();

private:
  int m_wrapped_int{ 0 };
};

/*
 - How to print Number obj on fmt stream?
 - Reference: https://fmt.dev/latest/api.html
 */
template<> struct fmt::formatter<Number>
{
  constexpr parse(format_parse_context &ctx) { return ctx.begin(); }
  template<typename FormatContext> auto format(const Number &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(), "Number : [{}]", obj.m_wrapped_int);
  }
};


#endif// NUMBER_H
