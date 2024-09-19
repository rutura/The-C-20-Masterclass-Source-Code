#pragma once


#include <string_view>
#include <memory>

class Dog;

void print_msg(std::string_view msg);
void do_something_with_dog_v1(std::unique_ptr<Dog> d);
void do_something_with_dog_v2(const std::unique_ptr<Dog>& d);
void unique_pointers();
void unique_pointers_as_func_param_or_return_type();
void unique_pointers_and_arrays();