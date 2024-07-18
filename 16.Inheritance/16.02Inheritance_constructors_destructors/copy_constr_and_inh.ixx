module;

#include <fmt/format.h>
#include <string>
#include <iostream>
#include <string_view>

export module copy_constr_and_inh;

namespace copy_constr_and_inh{

    //Person class
    export class Person
    {
    friend std::ostream &operator<<(std::ostream &, const Person &person);

    public:
    Person();
    Person(std::string_view fullname, int age, std::string_view address);
    Person(const Person &source);
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
    friend std::ostream &operator<<(std::ostream &out, const Engineer &operand);

    public:
    Engineer();
    Engineer(std::string_view fullname, int age, std::string_view address, int contract_count);
    Engineer(const Engineer &source);
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
    Engineer::Engineer() { std::cout << "Default constructor for Engineer called..." << std::endl; }

    Engineer::Engineer(std::string_view fullname, int age, std::string_view address, int contract_count_param)
    : Person(fullname, age, address), contract_count(contract_count_param)
    {
    std::cout << "Custom constructor for Engineer called..." << std::endl;
    }

    // BAD
    /*
    Engineer::Engineer(const Engineer& source)
        : contract_count(source.contract_count)
    {
        std::cout << "Custom copy constructor for Engineer called..." << std::endl;
    }
    */

    /*
    Engineer::Engineer(const Engineer& source)
        : Person(source.m_full_name,source.m_age,source.get_address())
            , contract_count(source.contract_count)
    {
        std::cout << "Custom copy constructor for Engineer called..." << std::endl;
    }
    */

    Engineer::Engineer(const Engineer &source) : Person(source), contract_count(source.contract_count)
    {
    std::cout << "Custom copy constructor for Engineer called..." << std::endl;
    }

    export std::ostream &operator<<(std::ostream &out, const Engineer &operand)
    {
    out << "Engineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
        << ",address : " << operand.get_address() << ",contract_count : " << operand.contract_count << "]";
    return out;
    }

    Engineer::~Engineer() {}




    //CivilEngineer class
    export class CivilEngineer : public Engineer
    {
    friend std::ostream &operator<<(std::ostream &, const CivilEngineer &operand);

    public:
    CivilEngineer();
    CivilEngineer(std::string_view fullname,
        int age,
        std::string_view address,
        int contract_count,
        std::string_view speciality);
    CivilEngineer(const CivilEngineer &source);
    ~CivilEngineer();

    void build_road()
    {
        // get_full_name(); // Compiler error
        /// m_full_name = "Daniel Gray"; //Compiler error
        // m_age = 45; // Compiler error

        add(10, 2);
        add(10, 2, 4);
    }

    public:
    // using Person::do_something; // Compiler error

    private:
    std::string m_speciality{ "None" };
    };
    //Implementation
    CivilEngineer::CivilEngineer() { std::cout << "Default constructor called for CivilEngineer ... " << std::endl; }


    CivilEngineer::CivilEngineer(std::string_view fullname,
    int age,
    std::string_view address,
    int contract_count,
    std::string_view speciality)
    : Engineer(fullname, age, address, contract_count), m_speciality(speciality)
    {
    std::cout << "Custom constructor called for CivilEngineer ... " << std::endl;
    }

    CivilEngineer::CivilEngineer(const CivilEngineer &source) : Engineer(source), m_speciality(source.m_speciality)
    {
    std::cout << "Custom copy constructor called for CivilEngineer ... " << std::endl;
    }

    /*
    //BAD : Compiler error - m_address is private to person
    CivilEngineer::CivilEngineer(std::string_view fullname,int age,
        std::string_view address,int contract_count, std::string_view speciality)
    {
        m_full_name = fullname;
        m_age = age;
        //m_address = address;
        m_speciality = speciality;
        std::cout << "Custom constructor called for CivilEnginner ... " << std::endl;
    }
    */

    /*
    CivilEngineer::CivilEngineer(std::string_view fullname,int age,
        std::string_view address,int contract_count, std::string_view speciality)
        :m_full_name(fullname),m_age(age),m_address(address),m_speciality(speciality)
    {

        std::cout << "Custom constructor called for CivilEnginner ... " << std::endl;
    }
    */

    export std::ostream &operator<<(std::ostream &out, const CivilEngineer &operand)
    {
    out << "CivilEngineer [Full name : " << operand.get_full_name() << ",age : " << operand.get_age()
        << ",address : " << operand.get_address() << ",contract_count : " << operand.get_contract_count()
        << ",speciality : " << operand.m_speciality << "]";

    return out;
    }


    CivilEngineer::~CivilEngineer() {}


}   // namespace copy_constr_and_inh