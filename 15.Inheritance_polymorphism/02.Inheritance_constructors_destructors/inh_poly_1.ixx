/*
    . How objects are constructed and destructed in inheritance
    . The constructors are called from the base class to the derived class
        . The base parts are constructed first, and then the derived parts
             are constructed on top of them.
    . The destructors are called from the derived class to the base class
    . The code: 
            . Inheritance Hierarchy:
                . Person is the base class.
                . Engineer inherits publicly from Person.
                . CivilEngineer inherits publicly from Engineer.

            . Constructors:
                . Base Class (Person):
                . Default Constructor: Initializes member variables with default
                     values and prints a message.
                . Parameterized Constructor: Initializes member variables with provided values and prints a message.
                . Derived Classes (Engineer and CivilEngineer):
                    . Default Constructors: Call the base class default constructor
                        (implicitly or explicitly) and print messages.
                    . Parameterized Constructors: Call the base class parameterized 
                        constructors and initialize their own members.

            . Destructors:
                . Called when the objects go out of scope or are deleted.
                . Destructors are called in the reverse order of constructors.
*/
module;

#include <fmt/format.h>
#include <string>

export module inh_poly_1;

namespace inh_poly_1 {
    // Base Class: Person
    export class Person {
    public:
        // Constructors
        Person() {
            fmt::println("Person: Default constructor called.");
        }

        Person(const std::string& fullname, int age, const std::string& address)
            : m_full_name(fullname), m_age(age), m_address(address) {
            fmt::println("Person: Parameterized constructor called.");
        }

        // Destructor
        ~Person() {
            fmt::println("Person: Destructor called.");
        }

        //A function that uses fmt::format to store info about the object in the returned sting
        std::string get_info() const {
            return fmt::format("Person [Full name: {}, Age: {}, Address: {}]", m_full_name, m_age, m_address);
        }

    protected:
        std::string m_full_name{"None"};
        int m_age{0};
        std::string m_address{"None"};
    };

    // Derived Class: Engineer
    export class Engineer : public Person {
    public:
        // Constructors
        Engineer() : Person() { // Explicitly calling base class constructor (optional here)
            fmt::println("Engineer: Default constructor called.");
        }

        Engineer(const std::string& fullname, int age, const std::string& address, int contracts)
            : Person(fullname, age, address), contract_count(contracts) {
            fmt::println("Engineer: Parameterized constructor called.");
        }

        // Destructor
        ~Engineer() {
            fmt::println("Engineer: Destructor called.");
        }

        //Get info
        std::string get_info() const {
            return fmt::format("Engineer [Full name: {}, Age: {}, Address: {}, Contracts: {}]", m_full_name, m_age, m_address, contract_count);
        }

    protected:
        int contract_count{0};
    };

    // Derived Class: CivilEngineer
    export class CivilEngineer : public Engineer {
    public:
        // Constructors
        CivilEngineer() : Engineer() { // Explicitly calling base class constructor (optional here)
            fmt::println("CivilEngineer: Default constructor called.");
        }

        CivilEngineer(const std::string& fullname, int age, const std::string& address, int contracts, const std::string& speciality)
            : Engineer(fullname, age, address, contracts), m_speciality(speciality) {
            fmt::println("CivilEngineer: Parameterized constructor called.");
        }

        // Destructor
        ~CivilEngineer() {
            fmt::println("CivilEngineer: Destructor called.");
        }

        //Get info
        std::string get_info() const {
            return fmt::format("CivilEngineer [Full name: {}, Age: {}, Address: {}, Contracts: {}, Speciality: {}]", m_full_name, m_age, m_address, contract_count, m_speciality);
        }

    private:
        std::string m_speciality{"None"};
    };

} // namespace inh_poly_1
