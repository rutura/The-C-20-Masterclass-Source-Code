#ifndef DOG_H
#define DOG_H

#include <iostream>
#include <string>

class Dog{
public : 
     Dog() = default;
     Dog(std::string_view name_param, std::string_view breed_param, unsigned int age_param);

     //Getters
     std::string_view get_name() const;
     std::string_view get_breed() const;
     unsigned int get_age() const;

     //Setters
     void set_name(std::string_view name_param);
     void set_breed(std::string_view breed_param);
     void set_age(unsigned int age);

     //Utility functions
     void print_info() const;

private : 
        std::string_view m_name;
        std::string_view m_breed;
        unsigned int m_age;
};


#endif // DOG_H
