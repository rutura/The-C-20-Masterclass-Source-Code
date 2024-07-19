module;

#include <fmt/format.h>
#include <string>
#include <string_view>

export module final_keyword;

/*
                            Animal
                   Feline                Bird
                Dog    Cat           Crow    Pigeon
        Bulldog            Wildcat

*/

namespace final_keyword{

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

    Animal::~Animal() {}



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

    Feline::~Feline() {}



    //Dog class
    export class Dog : public Feline
    {
    public:
    Dog() = default;
    Dog(std::string_view fur_style, std::string_view description);
    virtual ~Dog();

    virtual void bark() const { fmt::println("Dog::bark called : Woof!"); }

    // The run method in subclasses of dog can't be overrided
    // further, derived classes are forced to use the implmenetation in Dog
    void run() const override final { fmt::println("Dog::run called"); }
    };
    //Implementation
    Dog::Dog(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}

    Dog::~Dog() {}



    //Bulldog class
    export class BullDog : public Dog
    {
    public:
    BullDog();
    virtual ~BullDog();


    // Will throw a compiler error
    /*
    virtual void run() const override{
        fmt::println( "Bulldog::run() called" );
    }
    */
    };
    //Implementation
    BullDog::BullDog() {}

    BullDog::~BullDog() {}



    //Cat class
    export class Cat final : public Feline
    {
    public:
    Cat() = default;
    Cat(std::string_view fur_style, std::string_view description);
    virtual ~Cat();

    // Interesting fact #2
    // Useless virtual method. Cat is final, so no one will be deriving from
    // this class and have a chance to specialize it
    virtual void miaw() const { fmt::println("Cat::miaw() called for cat {}", m_description); }

    // This method is useful though
    void virtual run() const override
    {
        //
    }
    };
    //Implementation
    Cat::Cat(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}

    Cat::~Cat() {}



    //Wildcat class
    export class WildCat/* : public Cat */ // Can not derive from final base class
    {
    public:
    WildCat();
    ~WildCat();
    };
    //Implementation
    WildCat::WildCat() {}

    WildCat::~WildCat() {}



    //Bird class
    export class Bird : public Animal
    {
    public:
    Bird() = default;
    Bird(std::string_view wing_color, std::string_view description);

    virtual ~Bird();

    // This is contradictory : virtual and final have counter acting effects.
    // Final wins here
    virtual void fly() const final { fmt::println("Bird::fly() called for bird : {}", m_description); }

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
    virtual ~Crow();

    virtual void cow() const { fmt::println("Crow::cow called fro crow : {}", m_description); }

    // This will give a compiler error is fly is marked as final in Bird
    /*
    virtual void fly() const override{

    }
    */
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
    virtual ~Pigeon();

    virtual void coo() const { fmt::println("Pigeon::coo called for pigeon : {}", m_description); }
    };
    //Implementation

    Pigeon::Pigeon(std::string_view wing_color, std::string_view description) : Bird(wing_color, description) {}

    Pigeon::~Pigeon() {}


}   // namespace final_keyword