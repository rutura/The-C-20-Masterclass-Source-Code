module;

#include <string>
#include <fmt/format.h>

export module dog;

export class Dog
{
public:
  explicit Dog(std::string name_param);
  Dog() = default;
  ~Dog();

  void print_info() const { fmt::println("Printing dog: {}", dog_name); }

  std::string get_name() const { return dog_name; }

  void set_dog_name(const std::string &name) { dog_name = name; }

private:
  std::string dog_name{ "Puffy" };
};