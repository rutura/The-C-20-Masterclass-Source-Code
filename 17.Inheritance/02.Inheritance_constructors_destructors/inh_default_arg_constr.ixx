module;

#include <string>
#include <string_view>
#include <iostream>

export module inh_default_arg_constr;

namespace inh_default_arg_constr
{
    //Person class
    export class Person
    {
        friend std::ostream& operator<<(std::ostream& , const Person& person);
    public:
        Person() ;
        Person(std::string_view fullname,int age,
        const std::string address);
        ~Person();
        
        //Getters
        std::string get_full_name()const{
            return m_full_name;
        }
        
        int get_age()const{
            return m_age;
        }
        
        std::string get_address()const{
            return m_address;
        }


        int add(int a, int b) const{
            return a + b ;
        }

        int add(int a, int b, int  c) const{
            return a + b + c;
        }

        void do_something() const;
    public:
        std::string m_full_name{"None"};
    protected: 
        int m_age{0};
    private : 
        std::string m_address{"None"};
    };

    //Implementation

    Person::Person(){
        std::cout << "Default constructor for Person called..." << std::endl;
    }

    Person::Person(std::string_view fullname, int age,
        const std::string address) 
            : m_full_name{fullname}, m_age{age},
                m_address{address}
    {
    }

    void Person::do_something() const{
        std::cout << "Hello" << std::endl;
    }

    export std::ostream& operator<<(std::ostream& out , const Person& person){
    out << "Person [Full name :" << person.get_full_name() <<
                        ", Age:" << person.get_age() <<
                        ", Address:" << person.get_address() << "]";
    return out;
    }


    Person::~Person()
    {
    }



    //Engineer class
    export class Engineer : public Person
    {
    friend std::ostream& operator<<(std::ostream& out , const Engineer& operand);
    public:
        Engineer();
        ~Engineer();
        
        void build_something(){
            m_full_name = "John Snow"; // OK
            m_age = 23; // OK
            //m_address = "897-78-723"; Compiler error
        }

        int get_contract_count() const{
            return contract_count;
        }
        
    private : 
        int contract_count{0};
    };
    //Implementation
    Engineer::Engineer()
    {
        std::cout << "Default constructor for Engineer called..." << std::endl;
    }

    export std::ostream& operator<<(std::ostream& out , const Engineer& operand){
        out << "Engineer [Full name : " << operand.get_full_name() <<
                        ",age : " << operand.get_age() << 
                        ",address : " << operand.get_address() <<
                        ",contract_count : " << operand.contract_count << "]";
        return out;   
    }

    Engineer::~Engineer()
    {
    }


    //CivilEngineer class
    export class CivilEngineer : public Engineer
    {
        friend std::ostream& operator<<(std::ostream&, const CivilEngineer& operand);
    public:
        CivilEngineer();
        ~CivilEngineer() ;
        
        void build_road(){
            //get_full_name(); // Compiler error
            ///m_full_name = "Daniel Gray"; //Compiler error
            //m_age = 45; // Compiler error

            add(10,2);
            add(10,2,4);
        }

        public : 
            //using Person::do_something; // Compiler error
    private : 
        std::string m_speciality{"None"};

    };
    //Implementation
    CivilEngineer::CivilEngineer()
    {
        std::cout << "Default constructor called for CivilEnginner ... " << std::endl;
    }

    export std::ostream& operator<<(std::ostream& out, const CivilEngineer& operand){
        out << "CivilEngineer [Full name : " << operand.get_full_name() <<
                        ",age : " << operand.get_age() << 
                        ",address : " << operand.get_address() <<
                        ",contract_count : " << operand.get_contract_count() <<
                        ",speciality : " << operand.m_speciality << "]";
        return out;  
    }

    CivilEngineer::~CivilEngineer()
    {
    }

} // namespace inh_default_arg_constr