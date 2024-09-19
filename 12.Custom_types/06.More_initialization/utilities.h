#pragma once

#include <string_view>

// #1: Aggregate initialization
struct Point
{
    double x;
    double y;
};
// #2: Designated initializers
struct Component
{
    double x;
    double y;
    double z;
};


void print_point(const Point& p);
void print_component(const Component& c);
void print_msg(std::string_view msg);
void aggregate_initialization();
void designated_initializers();
