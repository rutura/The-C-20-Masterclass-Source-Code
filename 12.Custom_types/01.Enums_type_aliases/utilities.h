#pragma once

#include <string_view>

// Declare an enum type
// The default type associated with enum classes with C++ is int
// unsigned char : 0 ~ 255
enum class Month : char
{
    Jan = -1,
    January = Jan,
    Feb,
    Mar, Apr, May, Jun, Jul, Aug, Sep, Oct = 100, Nov, Dec
  };

//Old enums
enum Direction : unsigned char { TopLeft = 64, TopRight, Center, BottomLeft, BottomRight };

enum Tool { Pen, Marker, Eraser, Rectangle, Circle, PaintBucket };

void print_msg(std::string_view msg);
std::string_view month_to_string(Month month);
void enum_classes();
void using_enum();
void old_enums();
void type_aliases();