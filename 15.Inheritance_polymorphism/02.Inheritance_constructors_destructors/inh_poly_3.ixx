/*
        . Constructor Inheritance:

            . By default, constructors of a base class are not inherited by 
                derived classes. This means if you want to create an instance 
                of the derived class (Engineer) using the same parameters as 
                the base class (Person), you would need to define those 
                constructors explicitly in the derived class.
            . Using using Person::Person; tells the compiler to inherit all 
                constructors from the Person class, which allows instances 
                of Engineer to be created using the same constructor signatures 
                as Person. Pay attention to the fact that ALL constructors are
                inherited, including the default constructor.

            . You can add your own constructors to the derived class, which 
                will be called in addition to the inherited constructors. 
                This is useful when you need to initialize additional members 
                in the derived class.

        . Reduced Code Duplication:
            . This feature reduces code duplication since you don't have to 
                redefine the constructors in the Engineer class if they simply 
                forward the parameters to the base class. Instead, they are
                automatically available.

        . How this plays with the base access specifier: 

            . Public Inheritance:
                . Recap: When you inherit publicly, the public members of 
                    the base class remain public in the derived class, and 
                    the protected members remain protected. Private members 
                    of the base class are not accessible to the derived class 
                    at all.
                . Constructors: Public constructors of the base class are 
                    inherited as public in the derived class, while protected 
                    constructors are inherited as protected.

            . Protected Inheritance:
                . Recap: If you inherit a base class protectedly, all public 
                    and protected members of the base class become protected 
                    in the derived class, while private members remain 
                    inaccessible.
                . Constructors: Inherited constructors retain their access levels 
                    but can only be called within the derived class or its 
                    further derived classes.

            . Private Inheritance:
                . Recap: If you inherit a base class privately, all public and 
                    protected members become private in the derived class. 
                    The private members of the base class remain inaccessible.
                . Constructors: All inherited constructors become private in the 
                    derived class.
                                        
*/

module;

#include <fmt/format.h>
#include <string>

export module inh_poly_3;

namespace inh_poly_3{

    // Person class
    export class Person {
    public:
        // Default constructor
        Person() {
            fmt::print("Default constructor for Person called...\n");
        }

        // Custom constructor
        Person(std::string_view fullname, int age, std::string_view address)
            : m_full_name{fullname}, m_age{age}, m_address{address} {
            fmt::print("Custom constructor for Person called...\n");
        }

        // Copy constructor (not inheritable)
        Person(const Person &source)
            : m_full_name(source.m_full_name), m_age(source.m_age), m_address(source.m_address) {
            fmt::print("Custom copy constructor for Person called...\n");
        }

        // Destructor
        ~Person() {}

        // Returns formatted information about the person
        std::string get_info() const {
            return fmt::format("Person [Full name: {}, Age: {}, Address: {}]", m_full_name, m_age, m_address);
        }

        // Getters
        std::string get_full_name() const { return m_full_name; }
        int get_age() const { return m_age; }
        std::string get_address() const { return m_address; }


    private:
        std::string m_full_name{"None"};
        int m_age{0};
        std::string m_address{"None"};
    };

    // Engineer class
    export class Engineer : public Person {
        //The location of this using declaration doesn't matter.
        //We can build objects using the three param inherited constructor,
        //even if it shows up in a private section of the Engineer class.
        using Person::Person; // Inheriting constructors

    public:
        // Custom constructor
        Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
            : Person(fullname, age, address), m_contract_count(contract_count_param) {
            fmt::print("Custom constructor for Engineer called...\n");
        }

        // Destructor
        ~Engineer() {}

        // Returns formatted information about the engineer
        std::string get_info() const {
            return fmt::format("Engineer [Full name: {}, Age: {}, Address: {}, Contract Count: {}]",
                            get_full_name(), get_age(), get_address(), m_contract_count);
        }

        // Getter for contract count
        int get_contract_count() const { return m_contract_count; }

    private:
        int m_contract_count{0};
    };
    
} // namespace inh_poly_3