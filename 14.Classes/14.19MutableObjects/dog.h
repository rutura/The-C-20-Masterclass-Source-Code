#ifndef DOG_H
#define DOG_H

#include <iostream>
#include <string>

class Dog{
public : 
     Dog() = default;
     Dog(const std::string& name_param, const std::string& breed_param, unsigned int age_param);

     std::string& name(){
        return m_name;
     }
     const std::string& name() const{
        return m_name;
     }


     std::string& breed(){
        return m_breed;
     }
     const std::string& breed() const{
        return m_breed;
     }



     unsigned int& age(){
        return m_age;
     }
     const unsigned int& age() const{
        return m_age;
     }
 
     //Utility functions
     void print_info() const;

private : 
        std::string m_name;
        std::string m_breed;
        unsigned int m_age;
        mutable size_t m_print_info_count{};
};


#endif // DOG_H
