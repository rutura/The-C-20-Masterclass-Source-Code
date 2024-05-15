#include <fmt/format.h>
#include <string_view>

class Dog
{
public:
  Dog() = default;
  Dog(std::string_view name_param, std::string_view breed_param, int age_param);
  ~Dog();

private:
  std::string name;
  std::string breed;
  int *p_age{ nullptr };
};
Dog::Dog(std::string_view name_param, std::string_view breed_param, int age_param)
{
  name = name_param;
  breed = breed_param;
  p_age = new int;
  *p_age = age_param;
  fmt::println("Dog constructor called for {}", name);
}

Dog::~Dog()
{
  delete p_age;
  fmt::println("Dog destructor called for : {}", name);
}

void some_func()
{
  Dog *p_dog = new Dog("Fluffy", "Shepherd", 2);

  delete p_dog;// Causes for the destructor of Dog to be called
}


int main()
{

  some_func();


  fmt::println("Done!");
  return 0;
}