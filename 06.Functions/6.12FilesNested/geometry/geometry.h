#pragma once

// Same declarations as before - only the file's LOCATION changed. It now
// lives in the geometry/ subfolder. main.cpp will still write
// #include "geometry.h" (no path), because CMake adds this folder to the
// compiler's header search path.

double circle_area(double radius);
double circle_circumference(double radius);
