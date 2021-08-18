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
        /*
     //Getters
     std::string get_name() const;
     std::string get_breed() const;
     unsigned int get_age() const;

     //Setters
     void set_name(std::string name_param);
     void set_breed(std::string breed_param);
     void set_age(unsigned int age);
     */

     //Utility functions
     void print_info() const;
     const std::string& compile_dog_info() const{
        std::string dog_info = "dog_name : " + m_name
                              + " dog_breed : " + m_breed
                              + " dog_age :" + std::to_string(m_age);
      return dog_info;
     }

   unsigned int* jumps_per_minute() const{
        unsigned int jumps {5};
        return &jumps;
     }

private : 
        std::string m_name;
        std::string m_breed;
        unsigned int m_age;
};


#endif // DOG_H
