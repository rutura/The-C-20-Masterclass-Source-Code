module;

#include <fmt/format.h>
#include <string>
#include <string_view>

export module polymorphism_diff_levels;

namespace polymorphism_diff_levels{

    //Animal class  ==>> Feline
    //              ==>> Bird


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

    Animal::~Animal() {}



    //Feline class      ==>> Dog
    //                  ==>> Cat
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

    Feline::~Feline() {}



    //Dog class
    export class Dog : public Feline
    {
    public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view description);
    virtual ~Dog();

    virtual void bark() const { fmt::println("Dog::bark called : Woof!"); }

    virtual void breathe() const override { fmt::println("Dog::breathe called for : {}", m_description); }

    virtual void run() const override { fmt::println("Dog {} is running", m_description); }
    };
    //Implementation
    Dog::Dog(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}

    Dog::~Dog() {}



    //Cat class
    export class Cat : public Feline
    {
    public:
    Cat() = default;
    Cat(std::string_view fur_style, std::string_view description);
    virtual ~Cat();

    virtual void miaw() const { fmt::println("Cat::miaw() called for cat {}", m_description); }

    virtual void breathe() const { fmt::println("Cat::breathe called for : {}", m_description); }

    virtual void run() const override { fmt::println("Cat {} is running", m_description); }
    };
    //Implementation
    Cat::Cat(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}

    Cat::~Cat() {}



    //Bird class    ==>> Crow
    //              ==>> Pigeon
    export class Bird : public Animal
    {
    public:
    Bird() = default;
    Bird(std::string_view wing_color, std::string_view description);

    ~Bird();

    virtual void fly() const { fmt::println("Bird::fly() called for bird : {}", m_description); }

    private:
    std::string m_wing_color;
    };
    //Implementation
    Bird::Bird(std::string_view wing_color, std::string_view description) : Animal(description), m_wing_color(wing_color) {}

    Bird::~Bird() {}



    //Crow class
    export class Crow : public Bird
    {
    public:
    Crow() = default;
    Crow(std::string_view wing_color, std::string_view description);
    ~Crow();

    virtual void cow() const { fmt::println("Crow::cow called fro crow : {}", m_description); }

    virtual void breathe() const { fmt::println("Crow::breathe called for : {}", m_description); }

    virtual void fly() const override { fmt::println("Crow::fly() called for bird : {}", m_description); }
    };
    //Implementation
    Crow::Crow(std::string_view wing_color, std::string_view description) : Bird(wing_color, description) {}

    Crow::~Crow() {}



    //Pigeon class
    export class Pigeon : public Bird
    {
    public:
    Pigeon() = default;
    Pigeon(std::string_view wing_color, std::string_view description);
    ~Pigeon();

    virtual void coo() const { fmt::println("Pigeon::coo called for pigeon :{} ", m_description); }

    virtual void breathe() const { fmt::println("Pigeon::breathe called for :{} ", m_description); }

    virtual void fly() const override { fmt::println("Pigeon::fly() called for bird :{} ", m_description); }
    };
    //Implementation
    Pigeon::Pigeon(std::string_view wing_color, std::string_view description) : Bird(wing_color, description) {}

    Pigeon::~Pigeon() {}


}   // namespace polymorphism_diff_levels