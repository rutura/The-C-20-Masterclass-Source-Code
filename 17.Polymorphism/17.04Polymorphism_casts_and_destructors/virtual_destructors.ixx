module;

#include <fmt/format.h>
#include <string>
#include <string_view>

export module virtual_destructors;

namespace virtual_destructors{

    //Animal class
    export class Animal
    {
    public:
    Animal() = default;
    Animal(std::string_view description);
    virtual ~Animal();

    virtual void breathe() const { fmt::println("Animal::breathe called for : {}", m_description); }

    protected:
    std::string m_description;
    };
    //Implementation
    Animal::Animal(std::string_view description) : m_description(description) {}

    Animal::~Animal() { fmt::println("Animal destructor called"); }




    //Feline class
    export class Feline : public Animal
    {
    public:
    Feline() = default;
    Feline(std::string_view fur_style, std::string_view description);
    virtual ~Feline();

    virtual void run() const { fmt::println("Feline {} is running", m_description); }
    std::string m_fur_style;
    };
    //Implementation
    Feline::Feline(std::string_view fur_style, std::string_view description) : Animal(description), m_fur_style(fur_style)
    {}

    Feline::~Feline() { fmt::println("Feline destructor called"); }




    //Dog class
    export class Dog : public Feline
    {
    public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view description);
    virtual ~Dog();

    virtual void bark() const { fmt::println("Dog::bark called : Woof!"); }
    };
    //Implementation
    Dog::Dog(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}

    Dog::~Dog() { fmt::println("Dog destructor called"); }


}   // namespace virtual_destructors