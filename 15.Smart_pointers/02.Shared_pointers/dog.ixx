module;

#include <fmt/format.h>
#include <string>

export module dog;

export class Dog
{
public:
  explicit Dog(std::string name_param);
  Dog() = default;
  ~Dog();

  std::string get_name() const { return dog_name; }

  void set_dog_name(const std::string &name) { dog_name = name; }

  void print_info() const { fmt::println("Dog [ name : {}]", dog_name); }

private:
  std::string dog_name{ "Puffy" };
};

//Implementations
Dog::Dog(std::string name_param) : dog_name(name_param)
{
  fmt::println("Constructor for dog {} called ", dog_name, " called.");
}

Dog::~Dog() { fmt::println("Destructor for dog {} called", dog_name, " called"); }