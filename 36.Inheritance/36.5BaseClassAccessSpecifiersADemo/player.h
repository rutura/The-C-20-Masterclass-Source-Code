#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"

// Player will do public inheritance from Person
class Player : public Person
{
  friend std::ostream &operator<<(std::ostream &out, const Player &player);
  friend struct fmt::formatter<Player>;

public:
  Player();
  ~Player();

  // See the access we have to inherited members from Person
  void play()
  {

    m_full_name = "John Snow";// OK
    m_age = 55;// OK
    // m_address = "DSAKFD;ASKFJ;DKAS"; Compiler error
  }

private:
  int m_career_start_year{ 0 };
  double m_salary{ 0.0 };
  int health_factor{ 0 };// Let's say that it's 0~10
};

/**
* Player obj fmt's output overload
- reference: https://fmt.dev/latest/api.html
*/
template<> struct fmt::formatter<Player>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template<typename FormatContext> auto format(const Player &obj, FormatContext &ctx)
  {
    return format_to(
      ctx.out(), "Player [Full name: {}, age: {}, address: {}]", obj.get_full_name(), obj.get_age(), obj.get_address());
  }
};
#endif// PLAYER_H
