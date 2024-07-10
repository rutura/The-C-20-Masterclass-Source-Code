module;

#include <string>

export module car;

export class Car
{
public:
  Car() = default;
  Car(const std::string &color, int speed);
  ~Car();

  double get_speed() const { return m_speed; }
  std::string get_color() const { return m_color; }

private:
  std::string m_color;
  double m_speed;
};

Car::Car(const std::string &color, int speed) : m_color(color), m_speed(speed) {}

Car::~Car() {}