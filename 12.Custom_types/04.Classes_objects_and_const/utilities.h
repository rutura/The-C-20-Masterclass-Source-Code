#pragma once

#include <string_view>

class Dog;
void print_msg(std::string_view msg);
void const_objects();
// void function_taking_dog(Dog dog);
// void function_taking_dog_ref(Dog &dog_ref);
// void function_taking_const_dog_ref(const Dog &const_dog_ref);
// void function_taking_dog_p(Dog *p_dog);
// void function_taking_pointer_to_const_dog(const Dog *const_p_dog);
// void const_objects_as_function_parameters();
// void function_taking_dog(Dog dog);
// void function_taking_dog_ref(Dog &dog_ref);
// void function_taking_const_dog_ref(const Dog &const_dog_ref);
// void function_taking_dog_p(Dog *p_dog);
// void function_taking_pointer_to_const_dog(const Dog *const_p_dog);
// void const_member_functions();
void mutable_objects();