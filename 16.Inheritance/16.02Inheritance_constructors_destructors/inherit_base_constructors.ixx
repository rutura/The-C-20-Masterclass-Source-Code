module;

#include <fmt/format.h>
#include <string>
#include <iostream>
#include <string_view>

export module inherit_base_constructors;

namespace inherit_base_constructors{

    //Person class
    export class Person
    {
    friend std::ostream &operator<<(std::ostream &, const Person &person);

    public:
    Person();
    Person(std::string_view fullname, int age, std::string_view address);
    Person(const Person &source);// Copy constructors are not inheritable
    ~Person();

    // Getters
    std::string get_full_name() const { return m_full_name; }

    int get_age() const { return m_age; }

    std::string get_address() const { return m_address; }


    int add(int a, int b) const { return a + b; }

    int add(int a, int b, int c) const { return a + b + c; }

    void do_something() const;

    public:
    std::string m_full_name{ "None" };

    protected:
    int m_age{ 0 };

    private:
    std::string m_address{ "None" };
    };
    //Implementation
    Person::Person() { std::cout << "Default constructor for Person called..." << std::endl; }

    Person::Person(std::string_view fullname, int age, std::string_view address)
    : m_full_name{ fullname }, m_age{ age }, m_address{ address }
    {
    std::cout << "Custom constructor for Person called..." << std::endl;
    }

    Person::Person(const Person &source) : m_full_name(source.m_full_name), m_age(source.m_age), m_address(source.m_address)
    {
    std::cout << "Custom copy constructor for Person called..." << std::endl;
    }

    void Person::do_something() const { std::cout << "Hello" << std::endl; }

    export std::ostream &operator<<(std::ostream &out, const Person &person)
    {
    out << "Person [Full name :" << person.get_full_name() << ", Age:" << person.get_age()
        << ", Address:" << person.get_address() << "]";
    return out;
    }

    Person::~Person() {}



    //Engineer class
    export class Engineer : public Person
    {
    using Person::Person;// Inheriting constructors
    friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);
    friend struct fmt::formatter<Engineer>;

    public:
    /*
        Engineer();

        Engineer(const Engineer& source);
        */
    Engineer(std::string_view fullname, int age, std::string_view address, int contract_count);
    ~Engineer();

    void build_something()
    {
        m_full_name = "John Snow";// OK
        m_age = 23;// OK
        // m_address = "897-78-723"; Compiler error
    }

    int get_contract_count() const { return contract_count; }

    private:
    int contract_count{ 0 };
    };
    //Implementation
    /*
    Engineer::Engineer()
    {
        std::cout << "Default constructor for Engineer called..." << std::endl;
    }

    Engineer::Engineer(const Engineer& source)
        : Person(source)
            , contract_count(source.contract_count)
    {
        std::cout << "Custom copy constructor for Engineer called..." << std::endl;
    }
    */
    Engineer::Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
    : Person(fullname, age, address), contract_count(contract_count_param)
    {
    std::cout << "Custom constructor for Engineer called..." << std::endl;
    }

    export std::ostream &operator<<(std::ostream &out, const Engineer &operand)
    {
    out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
        << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
    return out;
    }

    Engineer::~Engineer() {}
}   // namespace inherit_base_constructors