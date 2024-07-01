module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

export const double PI{ 3.1415926535897932384626433832795 };

//Your first class
/*
export class Cylinder
{
public:
  // Functions (methods)
  double volume() { return PI * base_radius * base_radius * height; }

public:
  // Member variables
  double base_radius{ 1 };
  double height{ 1 };
};
*/

//Setting up constructors
/*
class Cylinder
{
public:
  // Constctors
  Cylinder()
  {
    base_radius = 2.0;
    height = 2.0;
  }

  Cylinder(double rad_param, double height_param)
  {
    base_radius = rad_param;
    height = height_param;
  }

  // Functions (methods)
  double volume() { return PI * base_radius * base_radius * height; }

private:
  // Member variables
  double base_radius{ 1 };
  double height{ 1 };
};
*/


//Defaulted constructors
/*
export class Cylinder
{
public:
  // Constctors
  Cylinder() = default;
  Cylinder(double rad_param, double height_param)
  {
    base_radius = rad_param;
    height = height_param;
  }

  // Functions (methods)
  double volume() { return PI * base_radius * base_radius * height; }

private:
  // Member variables
  double base_radius{ 1 };
  double height{ 1 };
};
*/


//Setters and getters
class Cylinder
{
public:
  // Constctors
  Cylinder() = default;
  Cylinder(double rad_param, double height_param)
  {
    base_radius = rad_param;
    height = height_param;
  }
  // Functions (methods)
  double volume() { return PI * base_radius * base_radius * height; }

  // Setter and getter methods
  double get_base_radius() { return base_radius; }
  double get_height() { return height; }

  void set_base_radius(double rad_param) { base_radius = rad_param; }

  void set_height(double height_param) { height = height_param; }

private:
  // Member variables
  double base_radius{ 1 };
  double height{ 1 };
};


//Module purview
export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


//Your first class
/*
export void your_first_class(){
	Cylinder cylinder1;// Objects
	fmt::println("volume : {}", cylinder1.volume());

	// Change the member variables
	cylinder1.base_radius = 10;
	cylinder1.height = 3;

	fmt::println("volume : {}", cylinder1.volume());

	cylinder1.height = 8;

	fmt::println("volume : {}", cylinder1.volume());
}
*/


//Using constructors
/*
export void using_constructors(){
	// Cylinder cylinder1(10,4); // Object
	Cylinder cylinder1;
	fmt::println("volume : {}", cylinder1.volume());
}
*/

//Defaulted constructors
/*
export void defaulted_constructors(){
	Cylinder cylinder1;
	fmt::println("volume : {}", cylinder1.volume());
}
*/


//Setters and getters
export void setters_and_getters(){
	Cylinder cylinder1(10, 10);
	fmt::println("volume : {}", cylinder1.volume());

	// Modify our object
	cylinder1.set_base_radius(100);
	cylinder1.set_height(10);

	fmt::println("volume : {}", cylinder1.volume());
}