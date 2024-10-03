/*
    . Closing in on private inheritance.
*/
module;

#include <iostream>
#include <string>

export module inh_poly_4;

namespace inh_poly_4{

    // Person class
    export class Person {
        friend std::ostream &operator<<(std::ostream &, const Person &person);
    public:
        Person() = default;
        Person(std::string_view fullname, int age, const std::string address);

        // Getters
        std::string get_full_name() const { return m_full_name; }
        int get_age() const { return m_age; }
        std::string get_address() const { return m_address; }

    public:
        std::string m_full_name{ "None" };
    protected:
        int m_age{ 0 };
    private:
        std::string m_address{ "None" };
    };

    // Implementations
    Person::Person(std::string_view fullname, int age, const std::string address)
        : m_full_name{ fullname }, m_age{ age }, m_address{ address } {}

    export std::ostream &operator<<(std::ostream &out, const Person &person) {
        out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
            << ", Address:" << person.get_address() << "]";
        return out;
    }

    // Engineer class
    export class Engineer : private Person {
        friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);
    public:
        Engineer() = default;

        void build_something() {
            m_full_name = "John Snow"; // OK
            m_age = 23; // OK
            // m_address = "897-78-723"; Compiler error
        }

    private:
        int contract_count{ 0 };
    };

    // Implementations
    export std::ostream &operator<<(std::ostream &out, const Engineer &operand) {
        out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
            << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
        return out;
    }

    // CivilEngineer class
    export class CivilEngineer : public Engineer {
        friend std::ostream &operator<<(std::ostream &, const CivilEngineer &operand);

    public:
        CivilEngineer() = default;

        void build_road() {
            // get_full_name(); // Compiler error
            // m_full_name = "Daniel Gray"; // Compiler error
            // m_age = 45; // Compiler error
        }

    private:
        std::string m_speciality{ "None" };
    };

    // Implementations
    export std::ostream &operator<<(std::ostream &out, const CivilEngineer &operand) {
        /*
        out << "CivilEngineer [Full name : " << operand.get_full_name() <<
                        ",age : " << operand.get_age() <<
                        //",address : " << operand.get_address() <<
                        ",contract_count : " << operand.contract_count <<
                        ",speciality : " << operand.m_speciality << "]";
        */
        return out;
    }
    
} // namespace inh_poly_4