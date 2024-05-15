#ifndef PERSON_H
#define PERSON_H

#include <fmt/format.h>
#include <string>
#include <string_view>
class Person
{
  friend std::ostream &operator<<(std::ostream &, const Person &person);
  friend struct fmt::formatter<Person>;

public:
  Person();
  Person(std::string_view fullname, int age, std::string_view address);
  Person(const Person &source);
  ~Person();

  // Getters
  std::string get_full_name() const { return m_full_name; }

  int get_age() const { return m_age; }

  std::string get_address() const { return m_address; }


  int add(int a, int b) const { return a + b; }

  int add(int a, int b, int c) const { return a + b + c; }

  void do_something() const;

public:
  std::string m_full_name{ "None" };

protected:
  int m_age{ 0 };

private:
  std::string m_address{ "None" };
};

/**
* Person obj fmt's output overload
- reference: https://fmt.dev/latest/api.html
*/
template<> struct fmt::formatter<Person>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template<typename FormatContext> auto format(const Person &obj, FormatContext &ctx) const
  {
    return format_to(
      ctx.out(), "Person [ Full name:{}, age: {}, address:{}]", obj.get_full_name(), obj.get_age(), obj.get_address());
  }
};

#endif// PERSON_H
