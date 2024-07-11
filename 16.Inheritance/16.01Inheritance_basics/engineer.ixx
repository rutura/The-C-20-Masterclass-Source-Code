module;

#include <fmt/format.h>
#include <string>
#include <iostream>

export module engineer;

//An Engineer class hierarchy. Be sure that Person doesn't conflict with others
// Person -> Engineer -> CivilEngineer

namespace Private_Inheritance_Up_Close{

    //Person
    export class Person
    {
    friend std::ostream &operator<<(std::ostream &, const Person &person);
    friend struct fmt::formatter<Person>;

    public:
    Person() = default;
    Person(std::string_view fullname, int age, const std::string address);
    ~Person();

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

    //Implementations
    Person::Person(std::string_view fullname, int age, const std::string address)
    : m_full_name{ fullname }, m_age{ age }, m_address{ address }
    {}

    std::ostream &operator<<(std::ostream &out, const Person &person)
    {
    out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
        << ", Address:" << person.get_address() << "]";
    return out;
    }

    Person::~Person() {}


    //Engineer
    export class Engineer : private Person
    {
    friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);
    public:
    Engineer();

    ~Engineer();

    void build_something()
    {
        m_full_name = "John Snow";// OK
        m_age = 23;// OK
        // m_address = "897-78-723"; Compiler error
    }

    private:
    int contract_count{ 0 };
    };

    //Implementations
    Engineer::Engineer() {}

    std::ostream &operator<<(std::ostream &out, const Engineer &operand)
    {
    out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
        << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
    return out;
    }

    Engineer::~Engineer() {}


    //CivilEngineer
    export class CivilEngineer : public Engineer
    {
    friend std::ostream &operator<<(std::ostream &, const CivilEngineer &operand);

    public:
    CivilEngineer();
    ~CivilEngineer();

    void build_road()
    {
        // get_full_name(); // Compiler error
        /// m_full_name = "Daniel Gray"; //Compiler error
        // m_age = 45; // Compiler error
    }

    private:
    std::string m_speciality{ "None" };
    };

    //Implementations
    CivilEngineer::CivilEngineer() {}

    std::ostream &operator<<(std::ostream &out, const CivilEngineer &operand)
    {
    /*
    out << "CivilEngineer [Full name : " << operand.get_full_name() <<
                    ",age : " << operand.get_age() <<
                    //",address : " << operand.get_address() <<
                    ",contract_count : " << operand.contract_count <<
                    ",speciality : " << operand.m_speciality << "]";
                    */


    return out;
    }


    CivilEngineer::~CivilEngineer() {}
}   //Private_Inheritance_Up_Close

