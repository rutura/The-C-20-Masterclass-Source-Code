#ifndef NUMBER_H
#define NUMBER_H

#include <fmt/format.h>
class Number
{
  friend std::ostream &operator<<(std::ostream &out, const Number &number);
  friend struct fmt::formatter<Number>;

public:
  Number() = delete;
  explicit Number(int value);

  // getter
  int get_wrapped_int() const { return m_wrapped_int; }

  /*
  auto operator<=>(const Number& right) const = default;
  auto operator<=> (int n) const{
      return m_wrapped_int <=> n;
  }
  bool operator==(const Number& right) const{
      return m_wrapped_int == right.m_wrapped_int;
  }
  bool operator==(int n){
      return m_wrapped_int == n;
  }
  */

  ~Number();

private:
  int m_wrapped_int{ 0 };
};

inline auto operator<=>(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() <= > right.get_wrapped_int());
}
inline auto operator<=>(int left, const Number &right) { return (left <= > right.get_wrapped_int()); }

inline bool operator==(const Number &left, const Number &right)
{
  return (left.get_wrapped_int() == right.get_wrapped_int());
}

inline bool operator==(int left, const Number &right) { return (left == right.get_wrapped_int()); }

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
