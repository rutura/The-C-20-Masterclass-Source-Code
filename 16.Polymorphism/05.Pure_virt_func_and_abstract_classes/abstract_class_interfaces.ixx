module;

#include <iostream>
#include <string>
#include <string_view>
#include <fmt/format.h>

export module abstract_class_interfaces;

namespace abstract_class_interfaces{

    //StreamInsertable class
    class StreamInsertable{
        friend std::ostream& operator<< (std::ostream& out, const StreamInsertable& operand);
        
    public : 
        virtual void stream_insert(std::ostream& out)const =0;
    };
    //Implementation
    export std::ostream& operator<< (std::ostream& out,const StreamInsertable& operand){
        operand.stream_insert(out);
        return out;
    }



    //Animal
    export class Animal :public StreamInsertable
    {
    public:
        Animal() = default;
        Animal(const std::string& description);
        ~Animal();
        
        virtual void breathe()const{
            std::cout << "Animal::breathe called for : " << m_description << std::endl;
        }
        
        //Stream insertable interface
        virtual void stream_insert(std::ostream& out)const override{
            out << "Animal [description : " << m_description <<"]" ;
        }
        
    protected: 
        std::string m_description;
    };
    //Implementation
    Animal::Animal(const std::string& description)
        : m_description(description)
    {
    }

    Animal::~Animal()
    {
    }



    //Feline
    export class Feline : public Animal
    {
    public:
        Feline() = default;
        Feline(const std::string& fur_style, const std::string& description);
        ~Feline();
        
        virtual void run() const{
            std::cout << "Feline " << m_description << " is running" << std::endl;
        }
        
        //Stream insertable interface
        virtual void stream_insert(std::ostream& out)const override{
            out << "Feline [description : " << m_description << ", fur_style : " << 
                    m_fur_style << "]";
        }
        std::string m_fur_style;
    };
    //Implementation
    Feline::Feline(const std::string& fur_style, const std::string& description)
        : Animal(description) , m_fur_style(fur_style)
    {
    }

    Feline::~Feline()
    {
    }



    //Dog
    export class Dog : public Feline
    {
    public:
        Dog() = default;
        Dog(const std::string& fur_style, const std::string& description);
        ~Dog();
        
        virtual void bark() const{
            std::cout << "Dog::bark called : Woof!" << std::endl;
        }
        
        virtual void stream_insert(std::ostream& out)const override{
            out << "Dog [description : " << m_description << ", fur_style : " << 
                    m_fur_style << "]";
        }

    };
    //Implementation
    Dog::Dog(const std::string& fur_style, const std::string& description)
        : Feline(fur_style,description)
    {
    }

    Dog::~Dog()
    {
    }




    //Cat
    export class Cat : public Feline
    {
    public:
        Cat() = default;
        Cat(const std::string& fur_style, const std::string& description);
        ~Cat();
        
        virtual void miaw() const{
            std::cout << "Cat::miaw() called for cat " << m_description << std::endl;
        }
        
        virtual void stream_insert(std::ostream& out)const override{
            out << "Cat [description : " << m_description << ", fur_style : " << 
                    m_fur_style << "]";
        }


    };
    //Implementation
    Cat::Cat(const std::string& fur_style, const std::string& description)
        : Feline(fur_style, description)
    {
    }

    Cat::~Cat()
    {
    }





    //Bird
    export class Bird : public Animal
    {
    public:
        Bird() = default;
        Bird(const std::string& wing_color, const std::string& description);
        
        ~Bird();
        
        virtual void fly() const{
            std::cout << "Bird::fly() called for bird : " << m_description << std::endl;
        }
        
        virtual void stream_insert(std::ostream& out)const override{
            out << "Bird [description : " << m_description << ", wing_color : " << 
                    m_wing_color << "]";
        }
        
    protected : 
        std::string m_wing_color;
    };
    //Implementation
    Bird::Bird(const std::string& wing_color, const std::string& description)
        : Animal(description) ,m_wing_color(wing_color)
    {
    }

    Bird::~Bird()
    {
    }




    //Crow
    export class Crow : public Bird
    {
    public:
        Crow() = default;
        Crow(const std::string& wing_color, const std::string& description);
        ~Crow();
        
        virtual void cow() const{
            std::cout << "Crow::cow called fro crow : " << m_description << std::endl;
        }
        
        virtual void stream_insert(std::ostream& out)const override{
            out << "Crow [description : " << m_description << ", wing_color : " << 
                    m_wing_color << "]";
        }

    };
    //Implementation
    Crow::Crow(const std::string& wing_color, const std::string& description)
        : Bird(wing_color,description)
    {
    }

    Crow::~Crow()
    {
    }



    //Pigeon
    export class Pigeon : public Bird
    {
    public:
        Pigeon() = default;
        Pigeon(const std::string& wing_color, const std::string& description);
        ~Pigeon();
        
        virtual void coo() const{
            std::cout << "Pigeon::coo called for pigeon : " << m_description << std::endl;
        }
        
        virtual void stream_insert(std::ostream& out)const override{
            out << "Pigeon [description : " << m_description << ", wing_color : " << 
                    m_wing_color << "]";
        }

    };
    //Implementation
    Pigeon::Pigeon(const std::string& wing_color, const std::string& description)
        : Bird(wing_color,description)
    {
    }

    Pigeon::~Pigeon()
    {
    }


    //Point class
    export class Point : public StreamInsertable{
    public : 
        Point() = default;
        Point(double x , double y)
            : m_x(x), m_y(y)
        {
        }

        virtual void stream_insert(std::ostream& out)const override{
            out << "Point [x: " << m_x << ",y: " << m_y << "]";
        }

    private : 
        double m_x;
        double m_y;
    };



}   // namespace abstract_class_interfaces