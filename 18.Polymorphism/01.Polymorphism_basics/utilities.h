#pragma once
#include <string_view>

namespace static_binding {
class Circle;
class Oval;
}

namespace polymorphism {
class Shape;
}

void print_msg(std::string_view msg);
void draw_circle(const static_binding::Circle &circle);
void draw_oval(const static_binding::Oval &oval);
void static_binding_demo();
void draw_shape(polymorphism::Shape *s);
void draw_shape_v1(const polymorphism::Shape &s_r);
void polymorphism_demo();
void sizes_and_slicing_demo();
void polymorphism_and_collections_demo();