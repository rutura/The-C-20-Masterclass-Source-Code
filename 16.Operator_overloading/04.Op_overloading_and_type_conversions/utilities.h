#pragma once

#include <string_view>

class Point;

void print_msg(std::string_view msg);
void use_point(const Point &p);
void custom_type_conversions();
void implicit_conversions_for_overloaded_binary_operators();
