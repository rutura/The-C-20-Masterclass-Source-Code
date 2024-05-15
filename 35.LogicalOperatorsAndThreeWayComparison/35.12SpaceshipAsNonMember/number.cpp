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

Number::~Number() {}
