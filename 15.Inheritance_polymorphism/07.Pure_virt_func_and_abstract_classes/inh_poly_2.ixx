/*
    This module demonstrates the use of abstract classes as interfaces in C++.

        . An abstract class with only pure virtual functions and no member variable can be used to model what is called an interface in Object Oriented Programming.

        . An interface is a specification of something that will be fully implemented in a derived class, but the specification itself resides in the abstract class


    . Key Points:
    - Abstract Classes and Pure Virtual Functions:
        - An abstract class in C++ is a class that contains at least one pure virtual function.
        - A pure virtual function is declared by assigning `0` to the function declaration.
        - Example: `virtual void stream_insert(std::ostream& out) const = 0;`

    - StreamInsertable Interface:
        - The `StreamInsertable` class is an abstract class that defines a pure virtual function `stream_insert`.
        - This function must be overridden by any derived class.
        - The `operator<<` is overloaded to use the `stream_insert` function for output.

    - Point Class:
        - The `Point` class also inherits from `StreamInsertable` and provides its own implementation of the `stream_insert` function.

    - Usage of Abstract Classes:
        - Abstract classes are used to define interfaces that must be implemented by derived classes.
        - They allow for polymorphic behavior, enabling the use of base class pointers or references to call derived class implementations.
        - This design promotes code reusability and flexibility.

*/

module;

#include <string>
#include <string_view>
#include <iostream>

export module inh_poly_2;

namespace inh_poly_2{

    // StreamInsertable interface
    class StreamInsertable {
        friend std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand) {
            operand.stream_insert(out);
            return out;
        }

    public:
        virtual void stream_insert(std::ostream& out) const = 0; // Pure virtual function
    };

    // Animal class
    export class Animal : public StreamInsertable {
    public:
        Animal() = default;
        Animal(const std::string& description) : m_description(description) {}
        virtual void breathe() const {
            std::cout << "Animal::breathe called for: " << m_description << std::endl;
        }
        
        // Stream insertable interface
        virtual void stream_insert(std::ostream& out) const override {
            out << "Animal [description: " << m_description << "]";
        }

    protected:
        std::string m_description;
    };

    // Feline class
    export class Feline : public Animal {
    public:
        Feline() = default;
        Feline(const std::string& fur_style, const std::string& description) 
            : Animal(description), m_fur_style(fur_style) {}
        
        virtual void run() const {
            std::cout << "Feline " << m_description << " is running" << std::endl;
        }

        // Stream insertable interface
        virtual void stream_insert(std::ostream& out) const override {
            out << "Feline [description: " << m_description << ", fur_style: " << m_fur_style << "]";
        }

    protected:
        std::string m_fur_style;
    };

    // Dog class
    export class Dog : public Feline {
    public:
        Dog() = default;
        Dog(const std::string& fur_style, const std::string& description)
            : Feline(fur_style, description) {}
        
        virtual void bark() const {
            std::cout << "Dog::bark called: Woof!" << std::endl;
        }

        virtual void stream_insert(std::ostream& out) const override {
            out << "Dog [description: " << m_description << ", fur_style: " << m_fur_style << "]";
        }
    };

    // Cat class
    export class Cat : public Feline {
    public:
        Cat() = default;
        Cat(const std::string& fur_style, const std::string& description)
            : Feline(fur_style, description) {}
        
        virtual void miaw() const {
            std::cout << "Cat::miaw() called for cat " << m_description << std::endl;
        }

        virtual void stream_insert(std::ostream& out) const override {
            out << "Cat [description: " << m_description << ", fur_style: " << m_fur_style << "]";
        }
    };

    // Bird class
    export class Bird : public Animal {
    public:
        Bird() = default;
        Bird(const std::string& wing_color, const std::string& description)
            : Animal(description), m_wing_color(wing_color) {}

        virtual void fly() const {
            std::cout << "Bird::fly() called for bird: " << m_description << std::endl;
        }

        virtual void stream_insert(std::ostream& out) const override {
            out << "Bird [description: " << m_description << ", wing_color: " << m_wing_color << "]";
        }

    protected:
        std::string m_wing_color;
    };

    // Crow class
    export class Crow : public Bird {
    public:
        Crow() = default;
        Crow(const std::string& wing_color, const std::string& description)
            : Bird(wing_color, description) {}
        
        virtual void cow() const {
            std::cout << "Crow::cow called for crow: " << m_description << std::endl;
        }

        virtual void stream_insert(std::ostream& out) const override {
            out << "Crow [description: " << m_description << ", wing_color: " << m_wing_color << "]";
        }
    };

    // Pigeon class
    export class Pigeon : public Bird {
    public:
        Pigeon() = default;
        Pigeon(const std::string& wing_color, const std::string& description)
            : Bird(wing_color, description) {}
        
        virtual void coo() const {
            std::cout << "Pigeon::coo called for pigeon: " << m_description << std::endl;
        }

        virtual void stream_insert(std::ostream& out) const override {
            out << "Pigeon [description: " << m_description << ", wing_color: " << m_wing_color << "]";
        }
    };

    // Point class
    export class Point : public StreamInsertable {
    public:
        Point() = default;
        Point(double x, double y) : m_x(x), m_y(y) {}

        virtual void stream_insert(std::ostream& out) const override {
            out << "Point [x: " << m_x << ", y: " << m_y << "]";
        }

    private:
        double m_x;
        double m_y;
    };
    
} // namespace inh_poly_2