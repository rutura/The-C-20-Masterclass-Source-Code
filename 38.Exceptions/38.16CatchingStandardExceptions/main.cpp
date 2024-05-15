#include <fmt/format.h>


class Animal
{
public:
  Animal(const std::string n) : m_name(n) {}
  Animal() = default;
  virtual ~Animal() {}
  virtual void breathe() const {}

protected:
  std::string m_name;
};

class Feline : public Animal
{
public:
  Feline(const std::string n) : Animal(n) {}

private:
  int speed;
};


int main()
{

  Animal animal;
  try {
    Feline &feline_ref = dynamic_cast<Feline &>(animal);
  } catch (std::exception &ex) {
    fmt::println("Something is wrong : {}", ex.what());
  }

  fmt::println("END.");


  return 0;
}