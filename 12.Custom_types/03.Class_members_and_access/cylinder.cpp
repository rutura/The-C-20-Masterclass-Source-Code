#include "cylinder.h"

const double PI{ 3.1415926535897932384626433832795 };


Cylinder::Cylinder(double rad_param, double height_param)
{
  base_radius = rad_param;
  height = height_param;
}

double Cylinder::volume() const { return PI * base_radius * base_radius * height; }


void Cylinder::set_base_radius(double rad_param) { base_radius = rad_param; }


void Cylinder::set_height(double height_param) { height = height_param; }