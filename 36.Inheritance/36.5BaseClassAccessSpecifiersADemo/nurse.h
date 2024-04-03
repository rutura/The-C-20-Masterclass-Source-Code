#ifndef NURSE_H
#define NURSE_H

#include "person.h"
#include <fmt/format.h>
// Nurse will do protected inheritance
class Nurse : protected Person
{
  friend std::ostream &operator<<(std::ostream &, const Nurse &operand);
  friend struct fmt::formatter<Nurse>;

public:
  Nurse();
  ~Nurse();

  void treat_unwell_person()
  {
    m_full_name = "John Snow";// OK
    m_age = 23;// OK
    // m_address = "897-78-723"; Compiler error
  }

private:
  int practice_certificate_id{ 0 };
};

/**
* Nurse obj fmt's output overload
- reference: https://fmt.dev/latest/api.html
*/
template<> struct fmt::formatter<Nurse>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template<typename FormatContext> auto format(const Nurse &obj, FormatContext &ctx)
  {
    return format_to(ctx.out(),
      "Nurse [FullName: {}, age: {}, address: {}, practice_certificate id: {}]",
      obj.get_full_name(),
      obj.get_age(),
      obj.get_address(),
      obj.practice_certificate_id);
  }
};

#endif// NURSE_H
