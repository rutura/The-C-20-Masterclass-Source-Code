#pragma once

#include <string_view>
#include <memory>

class Dog;

std::unique_ptr<Dog> get_unique_ptr();
void use_dog_v1(std::shared_ptr<Dog> dog);
void use_dog_v2(std::shared_ptr<Dog> &dog);
void use_dog_v3(const std::shared_ptr<Dog> &dog);
void print_msg(std::string_view msg);
void shared_pointers();
void unique_pointer_from_shared_pointer();
void shared_pointers_with_arrays();
void shared_pointers_as_function_parameters_and_return_types();