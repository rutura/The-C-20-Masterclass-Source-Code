/*
    . Exploring the use of the final specifier with inheritance. 
        . This specifier is used to prevent further inheritance or overriding of a function.
        . The hierarchy example: 
            Animal
            │
            ├── Feline
            │   ├── Dog
            │   │   └── BullDog
            │   │       └── run() (cannot be overridden; final in Dog)
            │   └── Cat (final) ──> No further inheritance allowed
            │       └── No class can inherit from Cat
            │
            ├── Bird
            │   ├── Crow
            │   │   └── fly() (cannot be overridden; final in Bird)
            │   └── Pigeon
            │       └── fly() (cannot be overridden; final in Bird)

        . In our examples: 
            . Dog::run Method:
                . The run() method in the Dog class is marked as final. This means that any 
                    class derived from Dog cannot override this method. For example, 
                    the BullDog class, which inherits from Dog, cannot provide its 
                    own implementation of run(). Attempting to do so would cause a 
                    compile-time error.
                . Effect: Prevents further overriding of run() in any subclass of Dog.

            . Cat Class:
                . The entire Cat class is marked as final. This means no other class 
                    can derive from Cat. The compiler will prevent any attempt to create 
                    a subclass of Cat. For example, trying to create a WildCat class 
                    that derives from Cat would result in a compile-time error.

                . Effect: Prevents any class from inheriting from Cat.

            . Bird::fly Method:
                . The fly() method in the Bird class is marked as final. Any subclass 
                    of Bird (e.g., Crow, Pigeon) cannot override this method. Attempting to 
                    override fly() in those subclasses will result in a compile-time error.

                . Effect: Prevents subclasses of Bird from providing their own fly() implementation.
*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module inh_poly_1;

namespace inh_poly_1{

    // Animal class
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
        Feline(std::string_view fur_style, std::string_view description)
            : Animal(description), m_fur_style(fur_style) {}
        virtual ~Feline() = default;

        virtual void run() const { fmt::println("Feline {} is running", m_description); }

    protected:
        std::string m_fur_style;
    };

    // Dog class
    export class Dog : public Feline {
    public:
        Dog() = default;
        Dog(std::string_view fur_style, std::string_view description)
            : Feline(fur_style, description) {}
        virtual ~Dog() = default;

        // The run method cannot be overridden further
        void run() const override final { fmt::println("Dog::run called"); }
        virtual void bark() const { fmt::println("Dog::bark called: Woof!"); }
    };

    // BullDog class
    export class BullDog : public Dog {
    public:
        BullDog() = default;
        virtual ~BullDog() = default;

        // Attempting to override run() will result in a compiler error
        /*
        virtual void run() const override {
            fmt::println("Bulldog::run() called");
        }
        */
    };

    // Cat class
    export class Cat final : public Feline {
    public:
        Cat() = default;
        Cat(std::string_view fur_style, std::string_view description)
            : Feline(fur_style, description) {}
        virtual ~Cat() = default;

        virtual void miaw() const { fmt::println("Cat::miaw() called for cat {}", m_description); }

        void run() const override { fmt::println("Cat::run called"); }
    };

    /*
    class WildCat : public Cat {    // Error: Cat is final
    };
    */

    // Bird class
    export class Bird : public Animal {
    public:
        Bird() = default;
        Bird(std::string_view wing_color, std::string_view description)
            : Animal(description), m_wing_color(wing_color) {}
        virtual ~Bird() = default;

        // fly() is marked as final, preventing further overriding
        virtual void fly() const final { fmt::println("Bird::fly() called for bird: {}", m_description); }

    private:
        std::string m_wing_color;
    };

    // Crow class
    export class Crow : public Bird {
    public:
        Crow() = default;
        Crow(std::string_view wing_color, std::string_view description)
            : Bird(wing_color, description) {}
        virtual ~Crow() = default;

        virtual void cow() const { fmt::println("Crow::cow called for crow: {}", m_description); }

        // Attempting to override fly() will result in a compiler error
        /*
        virtual void fly() const override {
        }
        */
    };

    // Pigeon class
    export class Pigeon : public Bird {
    public:
        Pigeon() = default;
        Pigeon(std::string_view wing_color, std::string_view description)
            : Bird(wing_color, description) {}
        virtual ~Pigeon() = default;

        virtual void coo() const { fmt::println("Pigeon::coo called for pigeon: {}", m_description); }
    };
    
} // namespace inh_poly_1