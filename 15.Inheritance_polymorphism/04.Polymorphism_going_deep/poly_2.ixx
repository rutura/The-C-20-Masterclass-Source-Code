/*
    . Polymorphism (virtual functions) can be introduced at any level in 
        the hierarchy. Take a look at the Animal hierarchy below: 

            // Class Hierarchy Chart:
            // 
            // Animal
            // ├── breathe()           // Introduced in Animal
            // └── Feline
            //     ├── run()          // Introduced in Feline
            //     └── Dog
            //         ├── bark()     // Introduced in Dog
            //         ├── breathe()  // Overrides Animal::breathe
            //         └── run()      // Overrides Feline::run
            //     └── Cat
            //         ├── miaw()     // Introduced in Cat
            //         ├── breathe()  // Overrides Animal::breathe
            //         └── run()      // Overrides Feline::run
            // └── Bird
            //     ├── fly()          // Introduced in Bird
            //     └── Crow
            //         ├── caw()      // Introduced in Crow
            //         ├── breathe()  // Overrides Animal::breathe
            //         └── fly()      // Overrides Bird::fly
            //     └── Pigeon
            //         ├── coo()      // Introduced in Pigeon
            //         ├── breathe()  // Overrides Animal::breathe
            //     

    . The breathe() virtual function is introduced at the Animal level
        . It sets up Shape polymorphism as I like to call it.
    . THe run() virtual function is introduced at the Feline level
        . It sets up Feline polymorphism.
    . At any level, you can set up a base pointer and use it to 
        manage objects of derived classes, and call virtual functions
        relevat to the polymorphic level you happen to be at.

*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module poly_2;

namespace poly_2{

    // Base class
    export class Animal {
    public:
        Animal() = default;
        Animal(std::string_view description) : m_description(description) {}
        virtual ~Animal() = default;
        virtual void breathe() const { fmt::println("Animal::breathe called for: {}", m_description); }
    protected:
        std::string m_description;
    };

    // Feline class
    export class Feline : public Animal {
    public:
        Feline() = default;
        Feline(std::string_view fur_style, std::string_view description) : Animal(description), m_fur_style(fur_style) {}
        virtual void run() const { fmt::println("Feline {} is running", m_description); }
    protected:
        std::string m_fur_style;
    };

    // Dog class
    export class Dog : public Feline {
    public:
        Dog() = default;
        Dog(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}
        virtual void bark() const { fmt::println("Dog::bark called: Woof!"); }
        virtual void breathe() const override { fmt::println("Dog::breathe called for: {}", m_description); }
        virtual void run() const override { fmt::println("Dog {} is running", m_description); }
    };

    // Cat class
    export class Cat : public Feline {
    public:
        Cat() = default;
        Cat(std::string_view fur_style, std::string_view description) : Feline(fur_style, description) {}
        virtual void miaw() const { fmt::println("Cat::miaw() called for cat: {}", m_description); }
        virtual void breathe() const override { fmt::println("Cat::breathe called for: {}", m_description); }
        virtual void run() const override { fmt::println("Cat {} is running", m_description); }
    };

    // Bird class
    export class Bird : public Animal {
    public:
        Bird() = default;
        Bird(std::string_view wing_color, std::string_view description) : Animal(description), m_wing_color(wing_color) {}
        virtual void fly() const { fmt::println("Bird::fly() called for bird: {}", m_description); }
    private:
        std::string m_wing_color;
    };

    // Crow class
    export class Crow : public Bird {
    public:
        Crow() = default;
        Crow(std::string_view wing_color, std::string_view description) : Bird(wing_color, description) {}
        virtual void caw() const { fmt::println("Crow::caw called for crow: {}", m_description); }
        virtual void breathe() const override { fmt::println("Crow::breathe called for: {}", m_description); }
        virtual void fly() const override { fmt::println("Crow::fly() called for bird: {}", m_description); }
    };

    // Pigeon class
    export class Pigeon : public Bird {
    public:
        Pigeon() = default;
        Pigeon(std::string_view wing_color, std::string_view description) : Bird(wing_color, description) {}
        virtual void coo() const { fmt::println("Pigeon::coo called for pigeon: {}", m_description); }
        virtual void breathe() const override { fmt::println("Pigeon::breathe called for: {}", m_description); }
        virtual void fly() const override { fmt::println("Pigeon::fly() called for bird: {}", m_description); }
    };
} // namespace poly_2