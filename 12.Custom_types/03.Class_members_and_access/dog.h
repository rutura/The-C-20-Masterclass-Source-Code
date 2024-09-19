#pragma once

#include <string>

//The this pointer
class Dog
{
public:
    Dog() = default;
    Dog(std::string_view name_param, std::string_view breed_param, int age_param);
    ~Dog();

    void print_info();

    // Setters
    // Chained calls using pointers
    /*Dog* set_dog_name(std::string_view name){
        //name = name; // This does nothing
        this->name = name;
        return this;
    }
    Dog* set_dog_breed(std::string_view breed){
        this->breed = breed;
        return this;
    }

    Dog* set_dog_age(int age){
        *(this->p_age) = age;
        return this;
    }*/

    // Chained calls using references
    Dog &set_dog_name(std::string_view name);
    Dog &set_dog_breed(std::string_view breed);
    Dog &set_dog_age(int age);

private:
    std::string name;
    std::string breed;
    int *p_age{ nullptr };
};