#pragma once

#include <string_view>

// Tools
constexpr int Pen{ 10 };
constexpr int Marker{ 20 };
constexpr int Eraser{ 30 };
constexpr int Rectangle{ 40 };
constexpr int Circle{ 50 };
constexpr int Ellipse{ 60 };


constexpr int Red{ 70 };
constexpr int Green{ 80 };
constexpr int Blue{ 90 };

void print_msg(std::string_view msg);
bool car();
bool house();
bool job();
void handleColor(int color);
void do_work();