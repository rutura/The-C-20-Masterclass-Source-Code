module;

#include <memory>
#include <string>
#include <fmt/format.h>

export module person;


export class Person
{
public:
  Person() = default;
  Person(std::string name);
  ~Person();

  // Member functions
  void set_friend(std::shared_ptr<Person> p)
  {
    // The assignment creates a weak_ptr out of p
    m_friend = p;
  }

private:
  std::weak_ptr<Person> m_friend;// Initialized to nullptr
  std::string m_name{ "Unnamed" };
};


//Implementations
Person::Person(std::string name) : m_name{ name }
{
  fmt::println("Constructor for person  {} called ", m_name, " called.");
}

Person::~Person() { fmt::println("Destructor for person  {} called ", m_name, " called."); }