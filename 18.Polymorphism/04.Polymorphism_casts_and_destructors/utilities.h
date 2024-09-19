#pragma once
#include "dynamic_casts.h"

#include <string_view>

void print_msg(std::string_view msg);
void virtual_destructors_demo();
void do_something_with_animal_ptr(dynamic_casts::Animal *animal);
void do_something_with_animal_ref(dynamic_casts::Animal &animal);
void dynamic_casts_demo();
void poly_func_and_destructors_demo();
void typeid_operator_demo();