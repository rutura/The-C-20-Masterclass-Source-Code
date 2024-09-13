module;

#include <fmt/format.h>
#include <string>

export module dog;


//Getters that double as setters.
/*
export class Dog
{
public:
  Dog() = default;
  Dog(const std::string &name_param, const std::string &breed_param, unsigned int age_param){
    m_name = name_param;
    m_breed = breed_param;
    m_age = age_param;
  }

  std::string &name() { return m_name; }
  const std::string &name() const { return m_name; }


  std::string &breed() { return m_breed; }
  const std::string &breed() const { return m_breed; }


  unsigned int &age() { return m_age; }
  const unsigned int &age() const { return m_age; }

  // //Getters
  // std::string get_name() const;
  // std::string get_breed() const;
  // unsigned int get_age() const;

  // //Setters
  // void set_name(std::string name_param);
  // void set_breed(std::string breed_param);
  // void set_age(unsigned int age);


  // Utility functions
  void print_info() const{
    fmt::println("Dog ({}): [ name: {}, bread: {}, age: {}]", 
        fmt::ptr(this), this->m_name, this->m_breed, this->m_age);
  }

private:
  std::string m_name;
  std::string m_breed;
  unsigned int m_age;
};
*/


//The this pointer
export class Dog
{
public:
  Dog() = default;
  Dog(std::string_view name_param, std::string_view breed_param, int age_param);
  ~Dog();

  void print_info()
  {
    fmt::println(
      "Dog ({}{}{}{}{}{}{}{}", fmt::ptr(this), ") : [ name : ", name, " breed : ", breed, " age : ", *p_age, "]");
  }

  // Setters
  // Chained calls using pointers
  /*
  Dog* set_dog_name(std::string_view name){
      //name = name; // This does nothing
      this->name = name;
      return this;
  }
  Dog* set_dog_breed(std::string_view breed){
      this->breed = breed;
      return this;
  }

  Dog* set_dog_age(int age){
      *(this->p_age) = age;
      return this;
  }
  */

  // Chained calls using references
  Dog &set_dog_name(std::string_view name)
  {
    // name = name; // This does nothing
    this->name = name;
    return *this;
  }
  Dog &set_dog_breed(std::string_view breed)
  {
    this->breed = breed;
    return *this;
  }

  Dog &set_dog_age(int age)
  {
    *(this->p_age) = age;
    return *this;
  }

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
  fmt::println("Dog constructor called for {}{}{}", name, " at ", fmt::ptr(this));
}

Dog::~Dog()
{
  delete p_age;
  fmt::println("Dog destructor called for {}{}{}", name, " at ", fmt::ptr(this));
}





