/*
    . Exploring copy semantics when inheritance is involved.
    . Copy Constructor Behavior:

        . Base Class Initialization: When a derived class object is copied,
             the base class's copy constructor is called first. This ensures
              that the base part of the derived object is initialized correctly.
        . Slicing: If a derived class object is assigned to a base class object,
             only the base part of the derived object is copied, leading to slicing. This can result in loss of derived class data.

    . Copy Assignment Operator Behavior:

        . Base Class Assignment: Similar to the copy constructor, when a derived
           class's copy assignment operator is invoked, the base class's  
            assignment operator should be called explicitly to ensure proper
            assignment of the base part.
        . Self-Assignment Check: Always check for self-assignment in the copy 
            assignment operator to prevent unintended behavior, particularly
             when the derived class and base class share resources.
*/
module;

#include <string>
#include <string_view>
#include <fmt/format.h>

export module inh_poly_2;

namespace inh_poly_2{

    // Person class
    export class Person {
    public:
        // Default constructor
        Person() { fmt::println("Default constructor for Person called..."); }

        // Custom constructor
        Person(std::string_view fullname, int age, std::string_view address)
            : m_full_name{fullname}, m_age{age}, m_address{address} {
            fmt::println("Custom constructor for Person called...");
        }

        // Copy constructor
        Person(const Person &source)
            : m_full_name{source.m_full_name}, m_age{source.m_age}, m_address{source.m_address} {
            fmt::println("Copy constructor for Person called...");
        }

        // Copy assignment operator
        Person &operator=(const Person &source) {
            fmt::println("Copy assignment operator for Person called...");
            if (this == &source) return *this;  // Check for self-assignment
            m_full_name = source.m_full_name;
            m_age = source.m_age;
            m_address = source.m_address;
            return *this;
        }

        ~Person() { fmt::println("Destructor for Person called..."); }

        //Get info
        std::string get_info() const {
            return fmt::format("Person [Full name: {}, Age: {}, Address: {}]", m_full_name, m_age, m_address);
        }

        // Getters
        std::string get_full_name() const { return m_full_name; }
        int get_age() const { return m_age; }
        std::string get_address() const { return m_address; }

    protected:
        std::string m_full_name{ "None" };
        int m_age{ 0 };

    private:
        std::string m_address{ "None" };
    };

    // Engineer class
    export class Engineer : public Person {
    public:
        // Default constructor
        Engineer() { fmt::println("Default constructor for Engineer called..."); }

        // Custom constructor
        Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
            : Person(fullname, age, address), m_contract_count{contract_count_param} {
            fmt::println("Custom constructor for Engineer called...");
        }

        // Copy constructor
        Engineer(const Engineer &source)
            : Person(source), m_contract_count{source.m_contract_count} {
            fmt::println("Copy constructor for Engineer called...");
        }

        // Copy assignment operator
        Engineer &operator=(const Engineer &source) {
            fmt::println("Copy assignment operator for Engineer called...");
            if (this == &source) return *this;  // Check for self-assignment
            Person::operator=(source);          // Delegate to Person's copy assignment
            m_contract_count = source.m_contract_count;
            return *this;
        }

        ~Engineer() { fmt::println("Destructor for Engineer called..."); }

        //Get info
        std::string get_info() const {
            return fmt::format("Engineer [Full name: {}, Age: {}, Address: {}, Contracts: {}]", get_full_name(), get_age(), get_address(), m_contract_count);
        }

        int get_contract_count() const { return m_contract_count; }

    private:
        int m_contract_count{ 0 };
    };

    // CivilEngineer class
    export class CivilEngineer : public Engineer {
    public:
        // Default constructor
        CivilEngineer() { fmt::println("Default constructor for CivilEngineer called..."); }

        // Custom constructor
        CivilEngineer(std::string_view fullname, int age, std::string_view address, int contract_count, std::string_view speciality)
            : Engineer(fullname, age, address, contract_count), m_speciality{speciality} {
            fmt::println("Custom constructor for CivilEngineer called...");
        }

        // Copy constructor
        CivilEngineer(const CivilEngineer &source)
            : Engineer(source), m_speciality{source.m_speciality} {
            fmt::println("Copy constructor for CivilEngineer called...");
        }

        // Copy assignment operator
        CivilEngineer &operator=(const CivilEngineer &source) {
            fmt::println("Copy assignment operator for CivilEngineer called...");
            if (this == &source) return *this;  // Check for self-assignment
            Engineer::operator=(source);        // Delegate to Engineer's copy assignment
            m_speciality = source.m_speciality;
            return *this;
        }

        ~CivilEngineer() { fmt::println("Destructor for CivilEngineer called..."); }

        //Get info
        std::string get_info() const {
            return fmt::format("CivilEngineer [Full name: {}, Age: {}, Address: {}, Contracts: {}, Speciality: {}]", get_full_name(), get_age(), get_address(), get_contract_count(), m_speciality);
        }

    private:
        std::string m_speciality{ "None" };
    };  
    
} // namespace inh_poly_2