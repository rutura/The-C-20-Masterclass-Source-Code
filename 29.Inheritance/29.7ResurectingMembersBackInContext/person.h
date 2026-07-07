#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <string_view>
class Person
{
    friend std::ostream& operator<<(std::ostream& , const Person& person);
public:
    Person() = default;
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


#endif // PERSON_H
