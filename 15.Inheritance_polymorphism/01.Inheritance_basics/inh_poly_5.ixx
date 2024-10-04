/*
        How Access Specifiers Work with Inheritance
            . Public Inheritance: Public members of the base class remain public 
                in the derived class, protected members remain protected, 
                and private members remain inaccessible.

            Protected Inheritance: Public and protected members of the base 
                class become protected in the derived class, while private 
                members remain inaccessible.

            Private Inheritance: Public and protected members of the base 
                class become private in the derived class, and private 
                members are inaccessible.

        Promotion via using
            . The using keyword can override these rules by "promoting" 
                members to different access levels. It’s a way of 
                selectively changing the accessibility of base class 
                members in the derived class without modifying the 
                base class itself.
            . It's a way to inherit the base class members with a 
                different access level.
            . If done to a member function, it brings in the whole
                overload set, you can't just cherry pick one overload.

            . The promoted members take the access level of the block 
                in which they are positioned in the derived class.
                If they are placed in the public block, they become
                public members in the derived class.
                
            . Private members of a base class can't be promoted to 
                public or protected in a derived class.
        Goal: 
            . Make the getters of the Person class accessible to the 
                most downstream class CivilEngineer's stream insertion
                operator.
*/
module;

#include <iostream>
#include <string>

export module inh_poly_5;

namespace inh_poly_5{

    export class Person {
        friend std::ostream& operator<<(std::ostream&, const Person& person);

    public:
        Person() = default;
        Person(std::string_view fullname, int age, const std::string address);

        // Getters
        std::string get_full_name() const {
            return m_full_name;
        }

        int get_age() const {
            return m_age;
        }

        std::string get_address() const {
            return m_address;
        }

        int add(int a, int b) const {
            return a + b;
        }

        int add(int a, int b, int c) const {
            return a + b + c;
        }

        void do_something() const;

    public:
        std::string m_full_name{"None"};

    protected:
        int m_age{0};

    private:
        std::string m_address{"None"};
    };

    // Implementation
    Person::Person(std::string_view fullname, int age, const std::string address)
        : m_full_name{fullname}, m_age{age}, m_address{address} {
    }

    void Person::do_something() const {
        std::cout << "Hello" << std::endl;
    }

    export std::ostream& operator<<(std::ostream& out, const Person& person) {
        out << "Person [Full name :" << person.get_full_name()
            << ", Age:" << person.get_age()
            << ", Address:" << person.get_address() << "]";
        return out;
    }

    // Engineer class
    export class Engineer : private Person {
        friend std::ostream& operator<<(std::ostream& out, const Engineer& operand);

    public:
        Engineer() = default;

        void build_something() {
            m_full_name = "John Snow"; // OK
            m_age = 23;                // OK
            // m_address = "897-78-723"; Compiler error
        }

    public:
        using Person::add;

    protected:
        using Person::get_full_name;
        using Person::get_age;
        using Person::get_address;
        // using Person::m_address; // Compiler error

        int get_contract_count() const {
            return contract_count;
        }

    private:
        int contract_count{0};
    };

    // Implementation
    export std::ostream& operator<<(std::ostream& out, const Engineer& operand) {
        out << "Engineer [Full name : " << operand.get_full_name()
            << ", age : " << operand.get_age()
            << ", address : " << operand.get_address()
            << ", contract_count : " << operand.contract_count << "]";
        return out;
    }

    // CivilEngineer class
    export class CivilEngineer : public Engineer {
        friend std::ostream& operator<<(std::ostream&, const CivilEngineer& operand);

    public:
        CivilEngineer() = default;

        void build_road() {
            // get_full_name(); // Compiler error
            // m_full_name = "Daniel Gray"; //Compiler error
            // m_age = 45; // Compiler error

            add(10, 2);
            add(10, 2, 4);
        }

    public:
        // using Person::do_something; // Compiler error

    private:
        std::string m_speciality{"None"};
    };

    // Implementation

    export std::ostream& operator<<(std::ostream& out, const CivilEngineer& operand) {
        out << "CivilEngineer [Full name : " << operand.get_full_name()
            << ", age : " << operand.get_age()
            << ", address : " << operand.get_address()
            << ", contract_count : " << operand.get_contract_count()
            << ", speciality : " << operand.m_speciality << "]";
        return out;
    }
} // namespace inh_poly_5
