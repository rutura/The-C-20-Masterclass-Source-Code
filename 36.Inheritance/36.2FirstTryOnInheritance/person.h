#ifndef PERSON_H
#define PERSON_H

#include <fmt/format.h>
#include <string>

class Person
{
  friend std::ostream &operator<<(std::ostream &out, const Person &person);

  friend struct fmt::formatter<Person>;

public:
  Person();
  Person(std::string &first_name_param, std::string &last_name_param);
  ~Person();

  // Getters
  std::string get_first_name() const { return first_name; }

  std::string get_last_name() const { return last_name; }

  // Setters
  void set_first_name(std::string_view fn) { first_name = fn; }
  void set_last_name(std::string_view ln) { last_name = ln; }

private:
  std::string first_name{ "Mysterious" };
  std::string last_name{ "Person" };
};

/**
* How to print Person obj on fmt's stream.
- reference: https://fmt.dev/latest/api.html
*/
template<> struct fmt::formatter<Person>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template<typename FormatContext> auto format(const Person &obj, FormatContext &ctx) const
  {
    return format_to(ctx.out(), "Person [{}, {}]", obj.get_first_name(), obj.get_last_name());
  }
};


#endif// PERSON_H
